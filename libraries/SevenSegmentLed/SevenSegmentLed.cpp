/*
  SevenSegmentLed.cpp - Library for common cathode 7 segment LED display
  Created by Ben Robinson July 2015
  
Copyright (c) [2015] [Ben Robinson]
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Arduino.h"
#include "SevenSegmentLed.h"

SevenSegmentLed::SevenSegmentLed(int cycleDelay)
{
  _cycleDelay=cycleDelay;
}

void SevenSegmentLed::setDigit(LedDigit digit)
{   
    switch(digit)
    {
      case Zero:
      zero();
      break;
      
      case One:
      one();
      break;
      
      case Two:
      two();
      break;
      
      case Three:
      three();
      break;
      
      case Four:
      four();
      break;
      
      case Five:
      five();
      break;
      
      case Six:
      six();
      break;
      
      case Seven:
      seven();
      break;      

      case Eight:
      eight();
      break; 

      case Nine:
      nine();
      break;

      case Point:
      point();
      break;          
  }  
}

void SevenSegmentLed::zero()
{
  off();
  digitalWrite(SegmentA, HIGH);  
  digitalWrite(SegmentB, HIGH);  
  digitalWrite(SegmentC, HIGH);  
  digitalWrite(SegmentD, HIGH);  
  digitalWrite(SegmentE, HIGH);  
  digitalWrite(SegmentF, HIGH);    
}

void SevenSegmentLed::one()
{
  off();  
  digitalWrite(SegmentB, HIGH);  
  digitalWrite(SegmentC, HIGH);  
}

void SevenSegmentLed::two()
{
  off();  
  digitalWrite(SegmentA, HIGH);  
  digitalWrite(SegmentB, HIGH);  
  digitalWrite(SegmentD, HIGH);  
  digitalWrite(SegmentE, HIGH);  
  digitalWrite(SegmentG, HIGH);  
}

void SevenSegmentLed::three()
{
  off();
  digitalWrite(SegmentA, HIGH);  
  digitalWrite(SegmentB, HIGH);  
  digitalWrite(SegmentC, HIGH);  
  digitalWrite(SegmentD, HIGH);  
  digitalWrite(SegmentG, HIGH);  
}

void SevenSegmentLed::four()
{
  off();
  digitalWrite(SegmentB, HIGH);  
  digitalWrite(SegmentC, HIGH);  
  digitalWrite(SegmentG, HIGH);  
  digitalWrite(SegmentF, HIGH);    
      
}

void SevenSegmentLed::five()
{
  off();
  digitalWrite(SegmentA, HIGH);  
  digitalWrite(SegmentC, HIGH);  
  digitalWrite(SegmentD, HIGH);  
  digitalWrite(SegmentG, HIGH);  
  digitalWrite(SegmentF, HIGH);  

}

void SevenSegmentLed::six()
{
  off();
  digitalWrite(SegmentA, HIGH);  
  digitalWrite(SegmentF, HIGH);  
  digitalWrite(SegmentG, HIGH);  
  digitalWrite(SegmentC, HIGH);  
  digitalWrite(SegmentE, HIGH);
  digitalWrite(SegmentF, HIGH);
  digitalWrite(SegmentD, HIGH);  
}

void SevenSegmentLed::seven()
{
  off();
  digitalWrite(SegmentA, HIGH);  
  digitalWrite(SegmentB, HIGH);  
  digitalWrite(SegmentC, HIGH);  
}

void SevenSegmentLed::eight()
{
  off();
  digitalWrite(SegmentA, HIGH);  
  digitalWrite(SegmentB, HIGH);  
  digitalWrite(SegmentC, HIGH);  
  digitalWrite(SegmentD, HIGH);  
  digitalWrite(SegmentE, HIGH);  
  digitalWrite(SegmentF, HIGH);  
  digitalWrite(SegmentG, HIGH);  
}

void SevenSegmentLed::nine()
{
  off();  
  digitalWrite(SegmentA, HIGH);  
  digitalWrite(SegmentB, HIGH);  
  digitalWrite(SegmentC, HIGH);    
  digitalWrite(SegmentF, HIGH);  
  digitalWrite(SegmentG, HIGH);  
}

void SevenSegmentLed::point()
{
  off();
  digitalWrite(DecimalPoint, HIGH);  
}


void SevenSegmentLed::cycle(LedDigit startDigit, LedDigit endDigit)
{
  int from = (int)startDigit;
  int to = (int)endDigit;
  for (int i = from; i <= to; i++)
  {
    setDigit((LedDigit)i);
    delay(_cycleDelay);     
  }    
}

void SevenSegmentLed::off()
{
  for(int i = 8; i <= 16; i++)
  {
    digitalWrite(i, LOW);    
  }
}