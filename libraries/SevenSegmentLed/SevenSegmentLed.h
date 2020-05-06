/*
  SevenSegmentLed.h - Library for common cathode 7 segment LED display
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


#ifndef SevenSegmentLed_h
#define SevenSegmentLed_h
#include "Arduino.h"

// Map this enum to the appropriate output pins on your Arduino
enum LedDisplay
{
  SegmentA = 2,
  SegmentB = 3,
  SegmentC = 4,
  SegmentD = 5,
  SegmentE = 6,
  SegmentF = 7,
  SegmentG = 8,
  DecimalPoint = 9,
};

enum LedDigit
{
  Zero = 0,
  One = 1,
  Two = 2,
  Three = 3,
  Four = 4,
  Five = 5,
  Six = 6,
  Seven = 7,
  Eight = 8,
  Nine = 9,
  Point = 10
};


class SevenSegmentLed
{
  public:
    void setDigit(LedDigit digit);
    void cycle(LedDigit startDigit, LedDigit endDigit);
    void off();
    SevenSegmentLed(int cycleDelay);
    
  private:
    void zero();
    void one();
    void two();
    void three();    
    void four();
    void five();
    void six();
    void seven();
    void eight();
    void nine();
    void point();     
    int _cycleDelay;        
};

#endif