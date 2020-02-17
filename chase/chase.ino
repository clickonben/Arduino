
void setup() 
{   
  for(int i = 0; i < 14; i++)
  {
    pinMode(i, OUTPUT);
  }
}

// the loop function runs over and over again forever
void loop() 
{ 

  chase(1,14,100);
  chase(12,0,100);
}

void chase(int start, int finish,int delayLength)
{
  if (start < finish)
  {
    for(int i = start; i < finish; i++)
    {
      flash(i,delayLength);     
    } 
  }
  else
  {
    for(int i = start; i >= finish; i--)
    {
      flash(i,delayLength);     
    } 
  }
}

void flash(int pin, int delayLength)
{
  digitalWrite(pin, HIGH);  
  delay(delayLength);                
  digitalWrite(pin, LOW);
}
