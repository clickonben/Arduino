const int buttonPin[4] = {8,9,10,11};     
const int ledPin[4] =  {4,5,6,7};      

void setup() {
  for(int i=0; i<4; i++)
  {
    pinMode(ledPin[i], OUTPUT);  
    pinMode(buttonPin[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() { 

  for(int i=0; i<4; i++)
  {
    int buttonState = digitalRead(buttonPin[i]);  
    if (buttonState == HIGH) 
    {    
      digitalWrite(ledPin[i], HIGH);
    } 
    else 
    {    
      digitalWrite(ledPin[i], LOW);
    }  
    Serial.print("Button: ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(buttonState);
  }

  
  
}
