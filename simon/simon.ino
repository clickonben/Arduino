int sequence[100];
int userSequence[100];
int sequenceLength;
int delayLength = 500;
int ledPinStart = 4;
int ledPinEnd = 7;
int buttonPinStart = 8;
int buttonPinEnd = 11;

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
    delay(delayLength);
    digitalWrite(sequence[i], LOW);  
    delay(delayLength);
    Serial.println(sequence[i]);
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
    Serial.println(correctButton);
    bool value = false;
    while(actualButton == 0)
    { 
      for (int i = buttonPinStart; i <= buttonPinEnd  && !value; i++)
      {     
          value = digitalRead(i);  
          if (value)
          {
            actualButton = i;            
            while(value)                      
            { 
              value = digitalRead(i);             
              digitalWrite(i-4, value);
            }          
          }          
      }      
    }
    Serial.print("Actual button: ");
    Serial.println(actualButton);
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
