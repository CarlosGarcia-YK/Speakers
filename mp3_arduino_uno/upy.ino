/*How to display images on arduino with 0.96" OLED
  subscribe for more arduino Tuorials and Projects
  Mission Critical
  https://www.youtube.com/channel/UCM6rbuieQBBLFsxszWA85AQ?sub_confirmation=1
  www.minov.in
 */


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);

const unsigned char* ricardoallArray[1] = {
  ricardo3
};
const unsigned char* ricardoBallArray[1] = {
  ricardoB3
};
const unsigned char* PauseButtonallArray[1] = {
  PauseButtonR
};
const unsigned char* ContinousButtonallArray[1] = {
  ContinousButtonR__1_
};

//-------------------------------------------------
void ricardo()
{
  display.clearDisplay();
  display.drawBitmap(0,0,ricardo3,128,64,WHITE);
  display.display();
  delay(4000);
  display.clearDisplay();
  display.display();
  }

void ricardoB()//
{
  display.clearDisplay();
  display.drawBitmap(0,0,ricardoB3,128,64,WHITE);
  display.display();
  delay(4000);
  display.clearDisplay();
  display.display();
  
  }
void pauseboton(){
  display.clearDisplay();
  display.drawBitmap(0,0,PauseButtonR,128,64,WHITE);
  display.display();
  
  }
void continueBoton()
{
  display.clearDisplay();
  display.drawBitmap(0,0,ContinousButtonR__1_,128,64,WHITE);
  display.display();
  delay(4000);
  display.clearDisplay();
  display.display();
  }

void before(){  //falta before 
  oled.clearDisplay();
    oled.setCursor(10,25);
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.print("Before");
    oled.display();
    oled.clearDisplay();
    ricardoB();
}
void continous(){ // 
  oled.clearDisplay();
    //continueBoton();
    //delay(3000);
    //oled.clearDisplay();
    ricardo();
    //delay(6000);
}
void stopped(){ 
  oled.clearDisplay();
    pauseboton();
    //delay(6000);
    
}
void start(){ // solo 1 falta
    display.clearDisplay();
    display.drawBitmap(0, 0, myBitmap, 128, 64, WHITE);
     display.display();
     delay(2000);
     display.clearDisplay();
      display.display();
     //
}
void volumen(){ //falta volumen 
  oled.clearDisplay();
    oled.setCursor(80,25);
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.print(vol);
    oled.display();
    delay(3000);
    oled.clearDisplay();
}
void setupy() 
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // here the 0x3c is the I2C address, check your i2c address if u have multiple devices.
  display.clearDisplay();
  delay(2000);

}

//--------------------------------------------------------------------

void album1(){
  
  if(t==0)
  {
    
    }
  
  }

//--------------------------------------------------------------------

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
