#include <DFRobotDFPlayerMini.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#define ancho 128
#define alto 32
#define oled_reset 2
Adafruit_SSD1306 oled(ancho,alto,&Wire,oled_reset); //All libraries used

 
//----------------------------------------------------------------------

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer; //The mp3 object is declared
void printDetail(uint8_t type, int value); //The mp3 data is shown
int reproducir=7; //Buttons are declared
int parar=3;
int siguiente=5;
int anterior=6;
int pot=A0;
bool pausa=false; //Pause is not activated
int t,play,sto,next,bef,vol,v,po,d,minutos, segundos; //Pins Configuration
long timer2 ; //Variables to be used for time
long timer=0 ;
//---------------------------------------------------------------------
void setup()
{
  mySoftwareSerial.begin(9600); //Monitor Configuration
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)")); //Initializing mp3 player
    
pinMode(reproducir,INPUT); //Inputs settings
pinMode(parar,INPUT);
pinMode(siguiente,INPUT);
pinMode(anterior,INPUT);
  
  
//------------------------------------------------------

if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    
    Serial.println(F("2.Please insert the SD card!"));
     oled.clearDisplay();
    oled.setCursor(10,25);
    oled.setTextColor(WHITE);
    oled.setTextSize(1);
    oled.print("2.Please insert the SD card!");
    oled.display();
  }
//--------------------------------------------

Serial.println(F("DFPlayer Mini online."));
myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
Wire.begin(); //The communication with oled is set
  oled.begin(SSD1306_SWITCHCAPVCC,0x3C); //The communication with oled starts
logo(); //UPY Logo is shown
delay(4000);
v=0; //Volume
t=1; //Track number

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3 (Empty)
 
  delay(1000);
  myDFPlayer.play(t); //The mp3 starts working
  timer=millis(); //Timer equals the actual time

}

void loop()
{
  static unsigned long timer= millis() ;
  long duration[9]={290000, 181000, 249000, 223000, 213000, 192000, 201000, 220000, 261000} ; //List created to recover the duration of each song
  play=digitalRead(reproducir); //All buttons are read
  sto=digitalRead(parar);
  next=digitalRead(siguiente);
  bef=digitalRead(anterior);
  po=analogRead(pot); //The value from the potentiometer is read
  v=po/34.1; //The value is turned into volume
  delay(20);
  if(pausa==false){ //If the device is not paused
  if (millis() - timer > duration[t-1]) { //If the playing time is greater than the duration of the song, it goes to the next one
    timer = millis(); //Timer is updated
    if(t==9){ //The number track is changed
      t=1;
   }else{
      t=t+1 ;
    }
    myDFPlayer.play(t);  //Play next mp3 song
    delay(2);
    album1(); //The image of the song is displayed
  }
  oled.clearDisplay(); //The display is cleared
  oled.setTextSize(2); //Settings for OLED (size, color, cursor)
  oled.setTextColor(WHITE);
  oled.setCursor(40,10) ;
  segundos=((millis()-timer)/1000)%60 ; //Time in seconds is calculated
  minutos=((millis()-timer)/1000)/60 ; //Time in minutes is calculated
  //Real time is shown
  if(minutos<10){
    oled.print("0");
  }
  oled.print(minutos);
  oled.print(":");
  if(segundos<10){
    oled.print("0");
  }
  oled.print(segundos);
  oled.display(); //Everything is shown
  }
  vol=v; 
  myDFPlayer.volume(vol);  //The mp3 player changes the volume

//----------------------
if ((play==0) && (pausa==true)) //When the player is paused and start button is pressed, then the track continues
{
    pausa=false; //There is no pause now
    myDFPlayer.start(); //The player starts where it was left
    timer=timer+millis()-timer2 ; //The timer is updated
    start(); //A transition image is shown
  
    
  }
//-------------------------
  if (bef==0){ //When before button is pressed, the previous song is pressed
 
    if(t==1){
      t=9 ;
    }else{
      t--;
    }
    myDFPlayer.play(t);//The previous track is played
    delay(2);
    pausa=false ; //There is no pause now
    timer = millis(); //Timer is updated
    before(); //Transition image is shown
  
}
//-------------
  if (next==0) //When next button is pressed, the next song is presse
  {
    if(t==9){
      t=1 ;
    }else{
      t++;
    }
    myDFPlayer.play(t);
    delay(2); 
    pausa=false ; //There is no pause now
    timer = millis(); //Timer is updated
    continous(); //Transition image is shown
        
  }

  if ((sto==0) && (play==1)) //If stop button is pressed when the song is being played, the player stops
  {
    myDFPlayer.pause(); //The player stops
    pausa=true; //Now there is pause
    timer2=millis(); //This variable will save the time the pause started
    stopped(); //An image is shown until there is no pause
  }
 
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
  
  
}
