
int latchPin = 7;
int clockPin = 8;
int dataPin = 6;

byte row[] = { B00001110, B00001101, B00001011, B00000111 };
byte column[] = { B00010000, B00100000, B01000000, B10000000 };

 

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() 
{  
  byte rowAccumulator = B00001111;
  for(byte i = 0; i < 4; i++)
  {  
    rowAccumulator = rowAccumulator & row[i];
    byte colAccumulator = 0;   
    for(byte j =0; j < 4; j++)
    {
      colAccumulator = colAccumulator | column[j];           
      digitalWrite(latchPin, LOW);  
      shiftOut(dataPin, clockPin, MSBFIRST, colAccumulator );
      shiftOut(dataPin, clockPin, MSBFIRST, 0 + rowAccumulator );
      digitalWrite(latchPin, HIGH);
      delay(200);
    }
  }
  
  rowAccumulator = B00001111;
  for(byte i = 0; i < 4; i++)
  {  
    rowAccumulator = rowAccumulator & row[i];
    byte colAccumulator = 0;   
    for(byte j =0; j < 4; j++)
    {
      colAccumulator = colAccumulator | column[j];           
      digitalWrite(latchPin, LOW);  
      shiftOut(dataPin, clockPin, MSBFIRST, colAccumulator >> 4 );
      shiftOut(dataPin, clockPin, MSBFIRST, 0 + rowAccumulator );
      digitalWrite(latchPin, HIGH);
      delay(200);
    }
  }

  rowAccumulator = B00001111;
  for(byte i = 0; i < 4; i++)
  {  
    rowAccumulator = rowAccumulator & row[i];
    byte colAccumulator = 0;   
    for(byte j =0; j < 4; j++)
    {
      colAccumulator = colAccumulator | column[j];           
      digitalWrite(latchPin, LOW);  
      shiftOut(dataPin, clockPin, MSBFIRST, 0 );
      shiftOut(dataPin, clockPin, MSBFIRST, colAccumulator + rowAccumulator );
      digitalWrite(latchPin, HIGH);
      delay(200);
    }
  }
}
