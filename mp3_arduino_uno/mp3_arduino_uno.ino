#include <DFRobotDFPlayerMini.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ancho 128
#define alto 64

#define oled_reset 2
Adafruit_SSD1306 oled(ancho,alto,&Wire,oled_reset);

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
int reproducir=7;
int parar=3;
int siguiente=5;
int anterior=6;
int pot=A0;
int led=7;
int t,play,sto,next,bef,vol,v,po,d;

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
t=1;
pinMode(reproducir,INPUT);
pinMode(parar,INPUT);
pinMode(siguiente,INPUT);
pinMode(anterior,INPUT);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  

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
    
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(t);  //Play the first mp3
  Wire.begin();
oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
v=0;
d=1;
}

void loop()
{
  
  play=digitalRead(reproducir);
  sto=digitalRead(parar);
  next=digitalRead(siguiente);
  bef=digitalRead(anterior);
  po=analogRead(pot);
    v=po/34.1;
    delay(20);
  if (vol!=v){
    vol=v;
    Serial.println (vol);
    myDFPlayer.volume(vol);
    
   
  }
  if (play==0){
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
  if (bef==0){
    delay (2);
    myDFPlayer.previous();
    before();
    t=t-1;
    if (t==0){
      t=1;
    }else{
      t=t;
    }
  }
  if (next==0){
    delay(2);
    t++;
    myDFPlayer.next();
    continous();
  }
  if (sto==0){
    delay(2);
    myDFPlayer.pause();
    stopped();
  }
 
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
  
  
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
void before(){
  oled.clearDisplay();
    oled.setCursor(10,25);
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.print("Before");
    oled.display();
    delay(6000);
    oled.clarDisplay();
}
void continous(){
  oled.clearDisplay();
    oled.setCursor(10,25);
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.print("Next");
    oled.display();
    delay(6000);
    oled.clearDisplay();
}
void stopped(){
  oled.clearDisplay();
    oled.setCursor(10,25);
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.print("Stop");
    oled.display();
    delay(6000);
    oled.clearDisplay();
}
void start(){
  oled.clearDisplay();
    oled.setCursor(10,25);
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.print("Play");
    oled.display();
    delay(6000);
    oled.clearDisplay();
    oled.setCursor(80,50);
    oled.setTextColor(WHITE);
    oled.setTextSize(1);
    oled.print("Playing... ");
    oled.print(t);
    oled.display();
}
void volumen(){
  oled.clearDisplay();
    oled.setCursor(80,25);
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.print(vol);
    oled.display();
    delay(3000);
    oled.clearDisplay();
}
