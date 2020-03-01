int sequence[100];
int userSequence[100];
int sequenceLength;
char colourText[7];

const int delayLength = 500;
const int offSet = 4;
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
  for(int i = offSet; i < offSet + 4; i++)
  {
    pinMode(i, OUTPUT);    
  }
  for(int i = offSet + 4; i < offSet + 8; i++)
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
  int randNumber = (int)random(0, 3);
  sequence[sequenceLength] = randNumber;
  sequenceLength ++;
  Serial.print("Sequence: ");
  Serial.println(sequenceLength);
  for(int i=0; i < sequenceLength; i++)
  {
    digitalWrite(sequence[i] + offSet, HIGH);
    playTone(sequence[i]);    
    delay(delayLength);
    digitalWrite(sequence[i] + offSet, LOW);  
    delay(delayLength);      
    setColourText(colourText, sequence[i]);    
    Serial.println(colourText);
  }
}

void readSequence()
{
  bool failed = false;
  int buttonOffSet = offSet + 4;
  for (int i = 0; i < sequenceLength && !failed; i++)
  {    
    int correctButton = sequence[i];
    int actualButton = 0;    
    Serial.print("Correct button: ");
    setColourText(colourText, correctButton);       
    Serial.println(colourText);
    bool value = false;
    while(actualButton == 0)
    { 
      for (int i = 0; i < 4 && !value; i++)
      {     
          value = digitalRead(i + buttonOffSet);  
          if (value)
          {
            actualButton = i;
            playTone(actualButton);            
            while(value)                      
            { 
              value = digitalRead(i + buttonOffSet);             
              digitalWrite(i + offSet, value);
            }                      
          }          
      }      
    }
    delay(delayLength);
    Serial.print("Actual button: ");
    setColourText(colourText, actualButton);    
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
