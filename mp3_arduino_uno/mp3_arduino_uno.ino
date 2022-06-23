#include <DFRobotDFPlayerMini.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //ag
#include <Adafruit_SSD1306.h>
#define ancho 128
#define alto 32
#define oled_reset 2//
Adafruit_SSD1306 oled(ancho,alto,&Wire,oled_reset); //Todos las librerias
 
//----------------------------------------------------------------------

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
int reproducir=7;
int parar=3;
int siguiente=5;
int x;
int anterior=6;
int pot=A0;
int led=7;
int busy=13 ;
bool inicio=false ;
bool first=false;
int acumulador,timer;
int t,play,sto,next,bef,vol,v,po,d,minutos, segundos; //Configuracion de pins
//---------------------------------------------------------------------
void setup()
{
  
  setupy();
  mySoftwareSerial.begin(9600); //Configuracion de monitor
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
    
pinMode(reproducir,INPUT); //Configuracion de inputs
pinMode(parar,INPUT);
pinMode(siguiente,INPUT);
pinMode(anterior,INPUT);
pinMode(busy,INPUT);
  
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
//--------------------------------------------

Serial.println(F("DFPlayer Mini online."));
myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);
  delay(1000);
  myDFPlayer.stop();
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
v=0;
d=1;
t=1;

}
}

void loop()
{
  if((inicio=true) && (first==false)){
    acumulador=millis();
    first=true ;
  }
  play=digitalRead(reproducir);
  sto=digitalRead(parar);
  next=digitalRead(siguiente);
  bef=digitalRead(anterior);
  if(digitalRead(busy)==LOW){
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(10,0) ;
  segundos=((millis()-timer)/1000)%60 ;
  minutos=((millis()-timer)/1000)/60 ;
  if(minutos<10){
    oled.print("0");
  }
  oled.print(minutos);
  oled.print(":");
  if(segundos<10){
    oled.print("0");
  }
  oled.print(segundos);
  album1();
  }
if (play==0)
{
    delay(2);
    d++;
    if (d==1){
    myDFPlayer.play();
    start();
    }
    else if(t or d !=1){
      myDFPlayer.start();
      start();
    }
  }
//-------------------------

//-------------
  if ((next==0) && (x==1))
  {
    delay(2);
    t++;
    myDFPlayer.next();
    continous();
  }

  if (sto==0)
  {
    delay(2);
    myDFPlayer.pause();
    stopped();
  }
 
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
  x=next; 
}
