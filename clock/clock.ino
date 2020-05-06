#include <Wire.h>
#include <DS3231.h>
#include "SevenSegmentLed.h"
SevenSegmentLed sevenSegmentLed(100);

DS3231 rtc;
bool Century=false;
bool h12;
bool PM;
 
// Code from the Demo Example of the DS3231 Library
void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  Wire.begin();
  setRTC(20,4,4,2,14,29,true);  
  
  
}
 
void loop() {
  delay(1000);
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
