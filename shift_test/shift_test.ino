
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

Letter message[] = { { Blue, 'H' }, 
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
  for(int i = 0; i < len; i++)
  { 
    for(int a = 0; a < 7; a++)
    {
      byte column = B00000001;   
      while(!intervalPassed())
      {
        for(int j = 0; j < 8; j++)        
        { 
          byte currentLetter = font[message[i].letter - 65][j] << a;
          byte nextLetter =  (i+1 < len ? font[message[i+1].letter - 65][j] : font[message[0].letter - 65][j]) >> 7-a ;
          byte row = currentLetter | nextLetter;          
          digitalWrite(latchPin, LOW); 
          shiftOut(dataPin, clockPin, LSBFIRST, 0);
          shiftOut(dataPin, clockPin, MSBFIRST, tempState ? row : 0);     
          shiftOut(dataPin, clockPin, LSBFIRST, column << j);
          shiftOut(dataPin, clockPin, LSBFIRST, !tempState? row : 0);           
          //  
          digitalWrite(latchPin, HIGH); 
        }     
      }
    }
  }
  tempState = !tempState;  
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
