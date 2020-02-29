int sequence[100];
int userSequence[100];
int sequenceLength;
char colourText[7];

const int delayLength = 500;
const int ledPinStart = 4;
const int ledPinEnd = 7;
const int buttonPinStart = 8;
const int buttonPinEnd = 11;
const int blueTone = 415;
const int redTone = 310;
const int yellowTone = 252;
const int greenTone = 209;
const int loseTone = 42;
const int buzzerPin = 12;

void setup() 
{  
  Serial.begin(9600);
  randomSeed(analogRead(0));
  sequenceLength = 0;
  for(int i = ledPinStart; i <= ledPinEnd; i++)
  {
    pinMode(i, OUTPUT);    
  }
  for(int i = buttonPinStart; i <= buttonPinEnd; i++)
  {
    pinMode(i, INPUT);    
  }
}

void loop() 
{   
  playSequence();
  readSequence();
  delay(delayLength);
}

void playSequence()
{  
  if (sequenceLength == 100)
  {
    lose();
  }
  int randNumber = (int)random(ledPinStart,ledPinEnd + 1);
  sequence[sequenceLength] = randNumber;
  sequenceLength ++;
  Serial.print("Sequence: ");
  Serial.println(sequenceLength);
  for(int i=0; i < sequenceLength; i++)
  {
    digitalWrite(sequence[i], HIGH);
    playTone(sequence[i]-4);    
    delay(delayLength);
    digitalWrite(sequence[i], LOW);  
    delay(delayLength);      
    setColourText(colourText, sequence[i] - 4);    
    Serial.println(colourText);
  }
}

void readSequence()
{
  bool failed = false;
  for (int i = 0; i < sequenceLength && !failed; i++)
  {    
    int correctButton = sequence[i] + 4; //Add 4 to the LED output to find the button input;
    int actualButton = 0;    
    Serial.print("Correct button: ");
    setColourText(colourText, correctButton - 8);       
    Serial.println(colourText);
    bool value = false;
    while(actualButton == 0)
    { 
      for (int i = buttonPinStart; i <= buttonPinEnd  && !value; i++)
      {     
          value = digitalRead(i);  
          if (value)
          {
            actualButton = i;
            playTone(i-8);            
            while(value)                      
            { 
              value = digitalRead(i);             
              digitalWrite(i-4, value);
            }                      
          }          
      }      
    }
    delay(delayLength);
    Serial.print("Actual button: ");
    setColourText(colourText, actualButton - 8);    
    Serial.println(colourText);    
    failed = (correctButton != actualButton); // If they pressed the wrong button in the sequence        
  }
  
  if(failed)
  {    
    lose();
  }
}

void lose()
{
  sequenceLength = 0;
  playTone(-1);    
  flashAll(5);
}

void flashAll(int times)
{  
  for(int i=0; i < times; i++)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    delay(delayLength);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    delay(delayLength);  
  }
}

void playTone(int colour)
{  
  switch(colour)
  {
    case 0:
    tone(buzzerPin, redTone, delayLength);
    break;
    case 1:
    tone(buzzerPin, greenTone, delayLength);
    break;
    case 2:
    tone(buzzerPin, yellowTone, delayLength);
    break;
    case 3:
    tone(buzzerPin, blueTone, delayLength);
    break;
    default:
    tone(buzzerPin, loseTone, delayLength);    
  }
}

void setColourText(char *textToSet, int pin)
{ 
  switch(pin)
  {
    case 0:
    strcpy(textToSet, "Red");    
    break;
    case 1:
    strcpy(textToSet, "Green");        
    break;
    case 2:
    strcpy(textToSet, "Yellow");    
    break;
    case 3:
    strcpy(textToSet, "Blue");        
    break;
    default:
    strcpy(textToSet, "Error");        
  }    
}
