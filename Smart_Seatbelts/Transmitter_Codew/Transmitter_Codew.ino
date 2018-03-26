//Made by Danish joshi(maniac1199) on 19/10/2016 ; Revised on 23/01/2017
//CBSE 2016-17 Science Exibition
//Smart Seat-belts 
//Transmitter_Unit

/* The seatbelt is connected to gnd in normal behaviour*/


//For RF Transmitter
#include <VirtualWire.h> 
//For OLED
#include "U8glib.h"
//For OLED Display
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0); 
//For RFID Card Reader
#include <SPI.h> 
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//Variables
int belt = A0 ;  //Pin for the belt connector (red) 
int state = 13; //Status Led 
int speed_pin = A1;  //Pot Pin {orange)
int speed_val;
int belt_read ; 
String belt_stat = "0"; //Init belt stat
String driver_card=""; //Driver Name
const int transmit_pin = 5; //Data Pin 
String final_msg; //Final data package

//Milis Variables
int state_m = LOW;
unsigned long previousMillis = 0; 
const long interval = 500;          

void setup()
{
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000); //Set up Virtual Wire
  pinMode(belt, INPUT_PULLUP);
  pinMode(state , OUTPUT);
  pinMode(speed_pin , INPUT_PULLUP);
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //Serial.println("Approximate your card to the reader...");
  //Serial.println();
}
void loop()
{
  
////////////////////Read Pins////////////////////

  speed_val = analogRead(speed_pin);
  speed_val = map(speed_val, 0, 1023, 0,100);  //Scaled Pot Value
  belt_read = analogRead(belt);  //Read pot value

////////////////////Check Belt and make data package////////////////////


  if (belt_read < 100) {
    String speed_val_str = String(speed_val);
    belt_stat = "1";
    final_msg=  speed_val_str + ";1";
    //Serial.println(belt_stat);
  }
  else if (belt_read > 100) {
    String speed_val_str = String(speed_val);
    belt_stat ="0";
    final_msg =  speed_val_str + ";0" ;
    //Serial.println(belt_stat);
  }

////////////////////RF SEND data package////////////////////
 
unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (state_m == LOW && speed_val >= 10  && driver_card=="Welcome Danish Joshi" ) {
        char charBuf[50];
        final_msg.toCharArray(charBuf, 50) ;
        send(charBuf);
       // Serial.println(charBuf);
        state_m = HIGH;
    } else {
        state_m = LOW;
    }
  }

////////////////////////////////////////////////////////
 /* if(speed_val > 10) {                          //Edit
  char charBuf[50];
  final_msg.toCharArray(charBuf, 50) ;
  send(charBuf);
  Serial.println(charBuf);
  delay(1000);
  }
*/

////////////////////OLED Speedometer////////////////////

  u8g.firstPage();  
  do {
  u8g.setFont(u8g_font_unifont); // Font
  u8g.setPrintPos(0, 20); 
  u8g.print(speed_val); //Text
  
  u8g.setFont(u8g_font_unifont); // Font
  u8g.setPrintPos(50, 20); 
  u8g.print("Km/h"); //Text
  
if(belt_stat == "1") {
  u8g.setFont(u8g_font_unifont); // Font
  u8g.setPrintPos(0, 50); 
  u8g.print("Seatbelt: OK"); //Text
}
else if(belt_stat == "0"){
  u8g.setFont(u8g_font_unifont); // Font
  u8g.setPrintPos(0, 50); 
  u8g.print("Seatbelt: NOT-OK"); //Text
}
else {
  u8g.setFont(u8g_font_unifont); // Font
  u8g.setPrintPos(0, 50); 
  u8g.print("Seatbelt: Error"); //Text
}
  u8g.setFont(u8g_font_unifont); // Font
  u8g.setPrintPos(0, 35); 
  u8g.print(driver_card); //Text
  
  } while( u8g.nextPage() );
  
//  delay(5);

////////////////////RFID Reader////////////////////

   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  
  if (content.substring(1) == "24 22 6F 85") //change here to add new
  {
    driver_card="Welcome Danish Joshi";
  }
 else  {
    driver_card="Access Denied";
    //delay(100);
  }
}

////////////////////RF Send Function////////////////////
void send(char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
}
