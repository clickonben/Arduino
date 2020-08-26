  #include <Wire.h>
#include <DS3231.h>

DS3231 rtc;
bool Century = false;
bool h12;
bool PM;
bool modified = false;
byte hour;
byte minute;
byte DoW;

const bool debug = true;
 
byte cathodes[4] = { B00010000, B00001000, B00000100, B00000010};

const byte dataPin = 2;
const byte clockPin = 3;
const byte latchPin = 4;
const byte modeButtonPin = 5;
const byte minusButtonPin = 6;
const byte plusButtonPin = 7;
const byte buzzerPin = 8; 

const byte dotsShiftPin = 0;
const byte redLEDShiftPin = 5;
const byte greenLEDShiftPin = 6;
const byte blueLEDShiftPin = 7;

const int redTone = 310;        // The tone in hertz of the LED/button 0 default colour red
const int greenTone = 209;      // The tone in hertz of the LED/button 0 default colour green
const int yellowTone = 252;     // The tone in hertz of the LED/button 0 default colour yellow
const int blueTone = 415;       // The tone in hertz of the LED/button 0 default colour blue    

const byte digits[] = { B01111110, B00110000, B01101101, B01111001, B00110011, B01011011, B01011111, B01110000, B01111111, B01111011 }; 

unsigned long flashPreviousMillis = 0;
long flashInterval = 1000;

unsigned long adjustPreviousMillis = 0;
long adjustInterval = 100;

bool dotsState;

enum ClockMode
{
  DisplayTime,
  SetTime,
  SetAlarm,
  DisplayTimeAlarmSet
};

ClockMode clockMode = DisplayTime;

void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  Wire.begin();
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(modeButtonPin, INPUT);
  pinMode(minusButtonPin, INPUT);
  pinMode(plusButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  //setRTC(20,5,7,4,15,18,true); 
  //getTime();
  //setAlarm();
}
 
void loop() 
{  
  for (int currentCathode = 0; currentCathode < 4; currentCathode++)   
  {
    if (clockMode == DisplayTime || clockMode == DisplayTimeAlarmSet)
    {
      getTime(); 
    }    
    updateDisplay(currentCathode);
    if(intervalPassed(flashInterval, &flashPreviousMillis))
    {
      dotsState = !dotsState;
      
      bool modeButtonState = digitalRead(modeButtonPin);      
      if(modeButtonState)
      {
        changeClockMode();        
      }         
      if (debug)
      {         
        printDebug(dotsState, modeButtonState, currentCathode);          
      }   
      if(isAlarm())
      {
        soundAlarm();           
      }
    }
    if(intervalPassed(adjustInterval, &adjustPreviousMillis))
    {
      if(clockMode == SetTime || clockMode == SetAlarm)
      {
        adjustClock();
      }      
    }  
  }
}

void updateDisplay(int cathodeID)
{
    int cathodeShiftCode = addShiftFlags(cathodes[cathodeID]);     
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, cathodeShiftCode ); 
    shiftOut(dataPin, clockPin, LSBFIRST, digits[getDigit(cathodeID)]);      
    digitalWrite(latchPin, HIGH);
}
void adjustClock()
{
  bool plusButtonState = digitalRead(plusButtonPin);  
  if(plusButtonState)
  {
    minute++;
    if(minute >= 60)
    {
      minute = 0;
      hour ++;
    }
    if(hour >= 24)
    {
      hour = 0;
    }
    modified = true;
  }
  
  bool minusButtonState = digitalRead(minusButtonPin); 
  if(minusButtonState)
  {
    minute--;
    if(minute >= 60)
    {
      minute = 59;
      hour --;
    }
    if(hour >= 24)
    {
      hour = 23;
    }
    modified = true;
  } 
}

byte addShiftFlags(byte shiftCode)
{
  bitWrite(shiftCode, dotsShiftPin, dotsState);
  switch(clockMode)
  {
    case DisplayTime:
    bitWrite(shiftCode, redLEDShiftPin, 0);
    bitWrite(shiftCode, blueLEDShiftPin, 0); 
    bitWrite(shiftCode, greenLEDShiftPin, 0); 
    break;      
    case SetAlarm:
    bitWrite(shiftCode, redLEDShiftPin, 1);
    bitWrite(shiftCode, blueLEDShiftPin, 0); 
    bitWrite(shiftCode, greenLEDShiftPin, 0); 
    break;  
    case SetTime:
    bitWrite(shiftCode, redLEDShiftPin, 0);
    bitWrite(shiftCode, blueLEDShiftPin, 1);
    bitWrite(shiftCode, greenLEDShiftPin, 0);  
    break;  
    case DisplayTimeAlarmSet:
    bitWrite(shiftCode, redLEDShiftPin, 0);
    bitWrite(shiftCode, blueLEDShiftPin, 0);  
    bitWrite(shiftCode, greenLEDShiftPin, 1);    
  }
  return shiftCode;
}

void changeClockMode()
{
  switch (clockMode)
  {
    case DisplayTime:
    clockMode = SetTime;
    break;
    case SetTime:
    clockMode = SetAlarm; 
    if (modified)
    {
      setCurrentTime();
      modified = false;
    }           
    getAlarm();
    break;
    case SetAlarm:
    if (modified)
    {
      setAlarm();
      modified = false;
    }       
    clockMode = DisplayTimeAlarmSet;
    enableAlarm();
    break;
    case DisplayTimeAlarmSet:
    clockMode = DisplayTime;
    disableAlarm();
    break;
  }
}

bool intervalPassed(long interval, unsigned long *previousMillis)
{
  long currentMillis = millis();
  bool passed = false;
  if(currentMillis - *previousMillis > interval) 
  {    
    *previousMillis = currentMillis;
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
    digit = (hour/10) % 10;
    break;  
    case 2:
    digit = hour % 10;
    break;
    case 1:
    digit = (minute/10) % 10;
    break;
    case 0:
    digit = minute % 10;
    break;
  }
  return digit;
}

void getTime()
{
  hour = rtc.getHour(h12, PM);
  minute = rtc.getMinute();
  DoW = rtc.getDoW();
}
void setCurrentTime()
{
  rtc.setHour(hour);
  rtc.setMinute(minute);
  rtc.setSecond(0);
}

void getAlarm()
{
  byte aHour, aMinute, discard;  
  bool bDiscard;
  rtc.getA1Time(discard, aHour, aMinute, discard, discard, bDiscard, bDiscard, bDiscard);
  hour = aHour;
  minute = aMinute;
}

void setAlarm()
{  
  byte alarmDoW; 
  byte alarmHour = hour;
  byte alarmMinute = minute;
  getTime();

  //If alarm time is later than current time set alarm day to today otherwise set it to tomorrow.
  if (alarmHour > hour || (alarmHour == hour && alarmMinute > minute))
  {
    alarmDoW = DoW;
  }
  else
  {
    alarmDoW = (DoW + 1) < 7 ? DoW + 1 : 0; // Set the alarm DoW to today + 1 (tomorrow) except if today + 1 is not a valid day then set it to 0 (Sunday)
  }
  
  rtc.setA1Time(alarmDoW, alarmHour, alarmMinute, 0, 0, true, false, false);  
}

void enableAlarm()
{
  rtc.turnOnAlarm(1);
}

void disableAlarm()
{
  rtc.turnOffAlarm(1);
}

bool isAlarm()
{
  bool alarm = false;
  if(rtc.checkAlarmEnabled(1))
  {
    byte aDoW, aHour, aMinute, discard;  
    bool bDiscard;
    rtc.getA1Time(aDoW, aHour, aMinute, discard, discard, bDiscard, bDiscard, bDiscard);
    if(DoW == aDoW && aHour == hour && aMinute <= minute && aMinute >= minute -5)
    {
      alarm = true;
    }
  } 
  return alarm; 
}

bool soundAlarm()
{
  tone(buzzerPin, redTone, 500);   
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

void printDebug(bool dotState, bool modeButtonState, byte cathodeID)
{
  Serial.print(rtc.getYear(), DEC);
  Serial.print("-");
  Serial.print(rtc.getMonth(Century), DEC);
  Serial.print("-");
  Serial.print(rtc.getDate(), DEC);
  Serial.print(" ");
  Serial.print(rtc.getDoW(), DEC);
  Serial.print(" ");
  Serial.print(rtc.getHour(h12, PM), DEC); //24-hr
  Serial.print(":");
  Serial.print(rtc.getMinute(), DEC);
  Serial.print(":");
  Serial.println(rtc.getSecond(), DEC);
  Serial.print("Dots: ");
  Serial.println(dotState ? "On" : "Off"); 
  Serial.print("Mode Button: ");
  Serial.println(modeButtonState ? "Down" : "Up" );
  Serial.print("CathodeID: ");
  Serial.println(cathodeID);
  Serial.print("Cathode Value: ");
  Serial.println(cathodes[cathodeID]);
  Serial.print("Minute: ");
  Serial.println(minute);  
  Serial.print("Hour: ");
  Serial.println(minute); 
  Serial.print("Clock Mode: ");
  Serial.println(clockMode);
  Serial.print("Alarm Enabled: ");
  Serial.println(rtc.checkAlarmEnabled(1) ? "Yes" : "No");
  Serial.print("Alarm !: ");
  Serial.println(isAlarm() ? "Yes" : "No");
  byte aHour, aMinute, aDoW, discard;  
  bool bDiscard, is12h, isPM;
  rtc.getA1Time(aDoW, aHour, aMinute, discard, discard, bDiscard, is12h, isPM);
  Serial.print("Alarm Time: ");
  Serial.print(aDoW);
  Serial.print(":");
  Serial.print(aHour);
  Serial.print(":");
  Serial.print(aMinute); 
  Serial.println("");
  Serial.print("Is 12 H: ");
  Serial.println(is12h ? "Yes" : "No");
  Serial.print("Is PM: ");
  Serial.println(isPM ? "Yes" : "No");
}
