#include <Wire.h>
#include <DS3231.h>

DS3231 rtc;
bool Century = false;
bool h12;
bool PM;
const bool debug = true;
 
byte cathodes[][3][4] = { { { B00001000, B00000100, B00000010, B00000001},
                            { B00001000, B00000100, B00000010, B00000001} },
                          { { B00001000, B00000100, B00000010, B00000001},
                            { B00000000, B00000000, B00000010, B00000001} },
                          { { B00001000, B00000100, B00000010, B00000001},
                            { B00001000, B00000100, B00000000, B00000000} } };

const byte dataPin = 2;
const byte clockPin = 3;
const byte latchPin = 4;
const byte buttonPin = 5;

const byte digits[] = { B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110 }; 

unsigned long currentMillis;
unsigned long previousMillis = 0;
long interval = 1000;

bool dotsState;

enum ClockMode
{
  Normal = 0,
  FlashHours = 1,
  FlashMinutes= 2
};

ClockMode mode = Normal;

void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  Wire.begin();
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  //setRTC(20,5,7,4,15,18,true);  
  
}
 
void loop() 
{  
  for (int currentCathode = 0; currentCathode < 4; currentCathode++)   
  {
    updateDisplay(currentCathode);
    if(intervalPassed())
    {
      dotsState = ! dotsState;
      bool buttonState = digitalRead(buttonPin);
      if (debug)
      {         
        printDebug(buttonState, dotsState);          
      }              
    }
  }
}

void updateDisplay(int cathodeID)
{
    int cathodeShiftCode = cathodes[dotsState][mode][cathodeID]; 
    bitWrite(cathodeShiftCode, 7, dotsState);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, cathodeShiftCode ); 
    shiftOut(dataPin, clockPin, LSBFIRST, digits[getDigit(cathodeID)]);      
    digitalWrite(latchPin, HIGH);
}
void printDebug(bool dotState, bool buttonState)
{
  Serial.print(rtc.getYear(), DEC);
  Serial.print("-");
  Serial.print(rtc.getMonth(Century), DEC);
  Serial.print("-");
  Serial.print(rtc.getDate(), DEC);
  Serial.print(" ");
  Serial.print(rtc.getHour(h12, PM), DEC); //24-hr
  Serial.print(":");
  Serial.print(rtc.getMinute(), DEC);
  Serial.print(":");
  Serial.println(rtc.getSecond(), DEC);
  Serial.print("Dots: ");
  Serial.println(dotState ? "On" : "Off"); 
  Serial.print("Button: ");
  Serial.println(buttonState ? "Down" : "Up" );
}

bool intervalPassed()
{
  currentMillis = millis();
  bool passed = false;
  if(currentMillis - previousMillis > interval) 
  {    
    previousMillis = currentMillis;
    passed = true;
  } 
  return passed;
}

byte getDigit(byte cathode)
{
  byte digit = 0;
  switch(cathode)
  {
    case 3:
    digit = (rtc.getHour(h12, PM)/10) % 10;
    break;  
    case 2:
    digit = rtc.getHour(h12, PM) % 10;
    break;
    case 1:
    digit = (rtc.getMinute()/10) % 10;
    break;
    case 0:
    digit = rtc.getMinute() % 10;
    break;
  }
  return digit;
}

void setRTC(byte year, byte month, byte day, byte dow, byte hour, byte minute, bool twentyFourHour)
{  
  rtc.setClockMode(!twentyFourHour); // set to 24 hour 
  if (year >= 0 && year < 100)
  { 
    rtc.setYear(year);
  }
  
  if(month > 0 && month < 13)
  {    
    rtc.setMonth(month);    
  }

  if(day > 0 && day < 32)
  {    
    rtc.setDate(day);
  }  

  if(dow > 0 && dow < 8)
  {    
    rtc.setDoW(dow); 
  }
  
  if(hour >= 0 && hour < 24)
  {    
    rtc.setHour(hour);
  }

  if(minute >= 0 && minute < 61)
  {
    rtc.setMinute(minute);
  }
  
  rtc.setSecond(0);   
  
}
