
byte dataPin = 2;
byte clockPin = 3;
byte latchPin = 4;



void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
 

}

void loop() {
 digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11110000 );  
  shiftOut(dataPin, clockPin, LSBFIRST, B10101010); 
  digitalWrite(latchPin, HIGH); 

}
