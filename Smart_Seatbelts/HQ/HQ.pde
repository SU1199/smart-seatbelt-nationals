//Made by Danish joshi(maniac1199) on 19/10/2016 ; Revised on 23/1/2017
//CBSE 2016-17 Science Exibition
//Smart Seat-belts 
//Control Pannel

import processing.serial.*;
import processing.sound.*;

Serial myPort;
String myText;
PImage bg;
int y;
String imp= "........";
int speed = 0;
int belt =0;
String locate = ": Samrala-Chowk";
SoundFile alert;
PrintWriter output; //Database Text File
String time;

void setup() {
  myPort = new Serial(this, "COM4", 9600);
  myPort.bufferUntil('n');
  size(1280, 720);
  bg = loadImage("bg.jpg");
  // Create a new file in the sketch directory
  output = createWriter("database.txt"); 
}


void draw() {
  background(bg);
  PFont font;
  font = loadFont("font(1).vlw");
  textFont(font, 55);
  text("Punjab Police Traffic Control System", 60, 180); 
  int m = minute() ;  
  int h = hour() ;    
  time ="( " + h + ":" + m + ") " ;
   while (myPort.available() > 0) {
    String inBuffer = myPort.readStringUntil('\n');   
    if (inBuffer != null) {
   //   println(inBuffer);
String init = inBuffer ;
String[] list = split(init, ';');
speed = int(list[0]);
belt = int(list[1]);
 }
  }
  if(belt == 0 && speed >= 60){
  PFont font2;
  font2 = loadFont("sub_f.vlw");
  textFont(font2, 35);
  text("\n PB10CM6259 ; Danish J. \n \n Fine Of ₹900 Sent to address\n \n Seatbelt Not Wearing  & Overspeeding at " +locate, 60, 250);
  alert = new SoundFile(this, "alert.mp3");
  alert.loop();
  alert.rate(0.5);
  output.println(time +"PB10CM6259 ; Danish J. ; Seatbelt Not Wearing  & Overspeeding at " + locate);
  output.flush();
  output.close();
}
  else if(belt == 1 && speed >= 60){
  PFont font2;
  font2 = loadFont("sub_f.vlw");
  textFont(font2, 35);
  text("\n PB10CM6259 ; Danish J. \n \n Fine Of ₹300 Sent to address \n \n Overspeeding at " +locate, 60, 250);
  alert = new SoundFile(this, "alert.mp3");
  alert.loop();
  alert.rate(0.5);
  output.println(time +"PB10CM6259 ; Danish J. ; Overspeeding at " + locate);
  output.flush();
  output.close();
}
  else if(belt == 0 && speed < 60){
  PFont font2;
  font2 = loadFont("sub_f.vlw");
  textFont(font2, 35);
  text("\n PB10CM6259 ; Danish J. \n \n Fine Of ₹600 Sent to address \n \n Seatbelt Not Wearing at " + locate, 60, 250);
  alert = new SoundFile(this, "alert.mp3");
  alert.loop();
  alert.rate(0.5);
  output.println(time +"PB10CM6259 ; Danish J. ; Seatbelt Not Wearing at " + locate);
  output.flush();
  output.close();
}
  else {
    
  PFont font3;
  font3 = loadFont("sub_f.vlw");
  textFont(font3, 35);
  text("...........", 60, 250);
  
  }
 }