const int dryTone = 415; 
const int ledPins[4] = { 2, 3, 4, 5 };
const int sensorPins[4] { A0, A1, A2, A3 };
const int inputPin = 6;
const int buzzerPin = 13;
const int alarmThreshold = 750;
const int cycleDelay = 1000;
const int timeoutDelay = 5000;

void setup() 
{ 
  Serial.begin(9600);

  for (int i =0; i < 5; i++)
  {
    pinMode(ledPins[i], OUTPUT);   
  } 
  
  pinMode(buzzerPin, OUTPUT);   
} 

void loop() 
{
  bool any = false;
  for (int i = 0; i < 4; i++)
  {
    int sensorValue = analogRead(sensorPins[i]); 
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" ");
    Serial.println(sensorValue);
    if (sensorValue > alarmThreshold) 
    { 
      digitalWrite(ledPins[i], HIGH);
      any = true;       
      Serial.println("High");
    }
    else
    {
      digitalWrite(ledPins[i], LOW);     
      Serial.println("Low");
    }      
  }
  if(any)
  {
    tone(buzzerPin, dryTone, 500);
    bool timeOut = digitalRead(inputPin);
    Serial.print("Timeout ");
    Serial.println(timeOut);
    if(timeOut)
    {
      for (int i = 0; i < 4; i++)
      {
         digitalWrite(ledPins[i], LOW);     
         Serial.println("Low");
      }
      delay(timeoutDelay);        
    }
  }  
  delay(cycleDelay);   
}
