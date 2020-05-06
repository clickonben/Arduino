  
#include "SevenSegmentLed.h"
SevenSegmentLed sevenSegmentLed(100);

void setup() {
  Serial.begin(115200);
  for(int i = 2; i <= 8; i++)
  {
    pinMode(i, OUTPUT);  
  }
}

void loop() {
  Serial.println("0");
  sevenSegmentLed.cycle(Zero, Zero);
  delay(500);
  Serial.println("1");
  sevenSegmentLed.cycle(Zero, One);  
  delay(500);
  Serial.println("2");
  sevenSegmentLed.cycle(Zero, Two);  
  delay(500);
  Serial.println("3");
  sevenSegmentLed.cycle(Zero, Three);
  delay(500);
  Serial.println("4");
  sevenSegmentLed.cycle(Zero, Four);
  delay(500);
  Serial.println("5");
  sevenSegmentLed.cycle(Zero, Five);
  delay(500);
  Serial.println("6");
  sevenSegmentLed.cycle(Zero, Six);
  delay(500);
  Serial.println("7");
  sevenSegmentLed.cycle(Zero, Seven);
  delay(500);
  Serial.println("8");
  sevenSegmentLed.cycle(Zero, Eight);
  delay(500);  
  Serial.println("9");
  sevenSegmentLed.cycle(Zero, Nine);
  delay(500);
}
