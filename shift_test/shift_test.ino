
byte dataPin = 2;
byte latchPin = 3;
byte clockPin = 4;
unsigned long currentMillis;
unsigned long previousMillis = 0;
long interval = 200;

enum Colour
{
  Red,
  Green,
  Blue
};

struct Letter
{
  Colour colour;
  char letter; 
};

Letter message[] = { { Green, 'H' }, 
                     { Red, 'E' }, 
                     { Blue, 'L' }, 
                     { Red, 'L' }, 
                     { Blue, 'O' }, 
                     { Red, 101 } }; 
int len;





byte font[][8]  { { B01110000,  //A
                    B10001000,
                    B10001000,
                    B10001000,
                    B11111000,
                    B10001000,
                    B10001000,
                    B00000000 },                  
                  { B11110000,  //B
                    B10001000,
                    B10001000,
                    B11110000,
                    B10001000,
                    B10001000,
                    B11110000,
                    B00000000 },              
                  { B01110000,  //C
                    B10001000,
                    B10000000,
                    B10000000,
                    B10000000,
                    B10001000,
                    B01110000,
                    B00000000 },
                  { B11100000,  //D
                    B10010000,
                    B10001000,
                    B10001000,
                    B10001000,
                    B10010000,
                    B11100000,
                    0         }, 
                  { B11111000,  //E
                    B10000000,
                    B10000000,
                    B11110000,
                    B10000000,
                    B10000000,
                    B11111000,
                    0         },
                
                  { B11111000,  //F
                    B10000000,
                    B10000000,
                    B11110000,
                    B10000000,
                    B10000000,
                    B10000000,
                    0         },
                
                  { B01110000,  //G
                    B10001000,
                    B10000000,
                    B10111000,
                    B10001000,
                    B10001000,
                    B01111000,
                    0         },
                
                  { B10001000,  //H
                    B10001000,
                    B10001000,
                    B11111000,
                    B10001000,
                    B10001000,
                    B10001000,
                    0         },
                
                  { B11100000,  //I
                    B01000000,
                    B01000000,
                    B01000000,
                    B01000000,
                    B01000000,
                    B11100000,
                    0         },
                
                  { B00111000,  //J
                    B00010000,
                    B00010000,
                    B00010000,
                    B00010000,
                    B10010000,
                    B01100000,
                    0         },
                
                  { B10001000,  //K
                    B10010000,
                    B10100000,
                    B11000000,
                    B10100000,
                    B10010000,
                    B10001000,
                    0         },
                
                  { B10000000,  //L
                    B10000000,
                    B10000000,
                    B10000000,
                    B10000000,
                    B10000000,
                    B11111000,
                    0         },
                
                  { B10001000,  //M
                    B11011000,
                    B10101000,
                    B10101000,
                    B10001000,
                    B10001000,
                    B10001000,
                    0         },
                
                  { B10001000,  //N
                    B10001000,
                    B11001000,
                    B10101000,
                    B10011000,
                    B10001000,
                    B10001000,
                    0         },
                
                  { B01110000,  //O
                    B10001000,
                    B10001000,
                    B10001000,
                    B10001000,
                    B10001000,
                    B01110000,
                    0         },
                
                  { B11110000,  //P
                    B10001000,
                    B10001000,
                    B11110000,
                    B10000000,
                    B10000000,
                    B10000000,
                    0         },
                
                  { B01110000,  //Q
                    B10001000,
                    B10001000,
                    B10001000,
                    B10101000,
                    B10010000,
                    B01101000,
                    0         },
                
                  { B11110000,  //R
                    B10001000,
                    B10001000,
                    B11110000,
                    B10100000,
                    B10010000,
                    B10001000,
                    0         },
                
                  { B01111000,  //S
                    B10000000,
                    B10000000,
                    B01110000,
                    B00001000,
                    B00001000,
                    B11110000,
                    0         },
                
                  { B11111000,  //T
                    B00100000,
                    B00100000,
                    B00100000,
                    B00100000,
                    B00100000,
                    B00100000,
                    0         },
                
                  { B10001000,  //U
                    B10001000,
                    B10001000,
                    B10001000,
                    B10001000,
                    B10001000,
                    B01110000,
                    0         },
                
                  { B10001000,  //V
                    B10001000,
                    B10001000,
                    B10001000,
                    B10001000,
                    B01010000,
                    B00100000,
                    0         },
                
                  { B10001000,  //W
                    B10001000,
                    B10001000,
                    B10101000,
                    B10101000,
                    B10101000,
                    B01010000,
                    0         },
                
                  { B10001000,  //X
                    B10001000,
                    B01010000,
                    B00100000,
                    B01010000,
                    B10001000,
                    B10001000,
                    0         },
                
                  { B10001000,  //Y
                    B10001000,
                    B10001000,
                    B01010000,
                    B00100000,
                    B00100000,
                    B00100000,
                    0         },
                
                  { B11111000,  //Z
                    B00001000,
                    B00010000,
                    B00100000,
                    B01000000,
                    B10000000,
                    B11111000,
                    0         },
                  
                  { 0,  //space
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0         } };
bool tempState = 0;

void setup() 
{
  Serial.begin(115200);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  len = sizeof(message) / sizeof(message[0]);
}

void loop() 
{  
  for(byte letterId = 0; letterId < len; letterId++)
  { 
    for(byte offSet = 0; offSet < 7; offSet++)
    {        
      while(!intervalPassed())
      {
        Letter currentLetter = message[letterId];
        Letter nextLetter = letterId+1 < len ? message[letterId+1] : message[0]; 
        shiftLetter(currentLetter, nextLetter, offSet);
      }
    }
  }
  tempState = !tempState;  
}

void shiftLetter(Letter currentLetter, Letter nextLetter, byte offSet)
{
  byte row = B00000001; 
  for(byte rowNo = 0; rowNo < 8; rowNo++)        
  {                       
    digitalWrite(latchPin, LOW);
    shiftRow(currentLetter, nextLetter, Green, offSet, rowNo);
    shiftRow(currentLetter, nextLetter, Blue, offSet, rowNo);     
    shiftOut(dataPin, clockPin, LSBFIRST, row << rowNo);
    shiftRow(currentLetter, nextLetter, Red, offSet, rowNo); 
    digitalWrite(latchPin, HIGH); 
  }  
}

void shiftRow(Letter currentLetter, Letter nextLetter, Colour colour, byte offSet, byte rowNo)
{
  byte currentLetterChar = font[currentLetter.letter - 65][rowNo] << offSet;
  byte nextLetterChar = font[nextLetter.letter - 65][rowNo]>> 7-offSet ; 

  if(currentLetter.colour == colour)
  {
     shiftOut(dataPin, clockPin, LSBFIRST, currentLetterChar); 
  }
  else if (nextLetter.colour == colour)
  {
    shiftOut(dataPin, clockPin, LSBFIRST, nextLetterChar);
  }
  else
  {
    shiftOut(dataPin, clockPin, LSBFIRST, 0);
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
