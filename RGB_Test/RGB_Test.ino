
const int red = 9;
const int green = 10;
const int blue = 11;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  analogWrite(red, 255);
  analogWrite(blue, 255);
  analogWrite(green, 255);
  fadeUp(red);
}

void loop() 
{ 
  fadeUp(blue);
  fadeDown(red);
  fadeUp(green); 
  fadeDown(blue);
  fadeUp(red);     
  fadeDown(green);    
}

void fadeUp(int pin)
{
  for (int i = 255; i > 0; i--)
  {
    analogWrite(pin, i);
    delay(10);
  }  
}

void fadeDown(int pin)
{
   for (int i = 0; i < 255; i++)
  {
    analogWrite(pin, i);
    delay(10);
  }
}
