byte cathodes[] = { B10000000, B01000000, B00100000, B00010000};

byte dataPin = 2;
byte clockPin = 3;
byte latchPin = 4;
byte digits[] = { B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110 }; 

unsigned long currentMillis;
unsigned long previousMillis = 0;
long interval = 100;

void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}


void loop() 
{
  for (int number = 9300; number > 0; number--)
  {   
    while(!intervalPassed())
    { 
      for (int currentCathode = 0; currentCathode < 4; currentCathode++)   
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, cathodes[currentCathode] ); 
        int digit = (number / ((int)pow(10, 3 - currentCathode))) % 10;
        shiftOut(dataPin, clockPin, LSBFIRST, digits[digit]);      
        digitalWrite(latchPin, HIGH);                   
      }  
    }      
  }
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
