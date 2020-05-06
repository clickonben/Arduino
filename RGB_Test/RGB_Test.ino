
const int red = 11;
const int green = 10;
const int blue = 9;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {

  fadeUp(red);
  fadeUp(blue);
  fadeUp(green);  
  fadeDown(red);  
  fadeDown(blue);
  fadeUp(red);    
  fadeDown(green);  
  fadeDown(red);  
}

void fadeUp(int pin)
{
  for (int i = 0; i < 255; i++)
  {
    analogWrite(pin, i);
    delay(10);
  }  
}

void fadeDown(int pin)
{
   for (int i = 255; i > 0; i--)
  {
    analogWrite(pin, i);
    delay(10);
  }
}
