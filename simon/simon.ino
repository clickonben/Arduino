int sequence[100];
int sequenceLength;

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
  if (sequenceLength == 100)
  {
    win();
  }
  int randNumber = (int)random(4,8);
  sequence[sequenceLength] = randNumber;
  sequenceLength ++;  
  playSequnce();  
}

void playSequnce()
{
  for(int i=0; i <= sequenceLength; i++)
  {
    digitalWrite(sequence[i], HIGH);
    delay(200);
    digitalWrite(sequence[i], LOW);  
    delay(200);  
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
