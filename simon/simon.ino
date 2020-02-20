int generatedSequence[100];
int userSequence[100];
int sequenceLength;
int delayLength = 500;

void setup() 
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  sequenceLength = 0;
  for(int i = 4; i < 8; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() 
{   
  playSequnce();  
}

void playSequnce()
{
  if (sequenceLength == 100)
  {
    win();
  }
  int randNumber = (int)random(4,8);
  generatedSequence[sequenceLength] = randNumber;
  sequenceLength ++;
  for(int i=0; i <= sequenceLength; i++)
  {
    digitalWrite(generatedSequence[i], HIGH);
    delay(delayLength);
    digitalWrite(generatedSequence[i], LOW);  
    delay(delayLength);  
  }
}

void win()
{
  sequenceLength = 0;
  for(int i=0; i = 5; i++)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    delay(500);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    delay(500);  
  }
}
