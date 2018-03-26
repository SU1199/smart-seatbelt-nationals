//Made by Danish joshi(maniac1199) on 19/10/2016 ; Revised On 23/1/2017
//CBSE 2016-17 Science Exibition
//Smart Seat-belts 
//Reciever_Unit
//Data pin = 11

#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
const int receive_pin = 8;

void setup()
{
Serial.begin(9600);
 vw_set_rx_pin(receive_pin);
vw_setup(2000);
vw_rx_start(); // Start the receiver
}
void loop()
{
if (vw_get_message(message, &messageLength)) // Non-blocking
{
for (int i = 0; i < messageLength; i++)
{
  Serial.write(message[i]);
  
}
Serial.println("");
}

}
