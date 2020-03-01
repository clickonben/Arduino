int sequence[100];
int userSequence[100];
int sequenceLength = 0;
char colourText[7];

const int delayLength = 500;    // The delay between each step in the sequence, reduce this to speed up the game.
const int offSet = 4;           // The actual output pin LED pin 0 is copnnected to.   
const int redTone = 310;        // The tone in hertz of the LED/button 0 default colour red
const int greenTone = 209;      // The tone in hertz of the LED/button 0 default colour green
const int yellowTone = 252;     // The tone in hertz of the LED/button 0 default colour yellow
const int blueTone = 415;       // The tone in hertz of the LED/button 0 default colour blue    
const int loseTone = 42;        // The tone in hertz to play when player makes a mistake
const int buzzerPin = 12;       // The pin to which the buzzer as attached

// Seed the random number generator and set pins to correct mode. 
void setup() 
{  
  Serial.begin(9600);          // Disable this if you wish to use pin 0 or 1 as normal output pins. This will disable the serial monitor. 
  randomSeed(analogRead(0));
  sequenceLength = 0;
  for(int i = offSet; i < offSet + 4; i++)
  {
    pinMode(i, OUTPUT);    
  }
  for(int i = offSet + 4; i < offSet + 8; i++)
  {
    pinMode(i, INPUT);    
  }

  pinMode(buzzerPin, OUTPUT);
}

void loop() 
{   
  playSequence();
  readSequence();
  delay(delayLength);
}

void playSequence()
{ 
  // Generate a random number between 0 and 3 and add it to the end of the sequence
  int randNumber = (int)random(0, 4);
  sequence[sequenceLength] = randNumber;
  sequenceLength ++;
  Serial.print("Sequence: ");
  Serial.println(sequenceLength);

  //Play back the sequence from beginning to end.
  for(int i=0; i < sequenceLength; i++)
  {
    digitalWrite(sequence[i] + offSet, HIGH);
    playTone(sequence[i]);    
    delay(delayLength);
    digitalWrite(sequence[i] + offSet, LOW);  
    delay(delayLength);

    //Output debug information
    setColourText(colourText, sequence[i]);    
    Serial.println(colourText);
  }
}

void readSequence()
{
  bool failed = false;
  int buttonOffSet = offSet + 4;                        // Set button offset so that button pin 0 = equals LED pin 0 + 4
  
  for (int i = 0; i < sequenceLength && !failed; i++)   // Step through the sequence until the user makes a mistake or the end is reached
  { 
    //  Set the correct button and set the input values to defaults.
    int correctButton = sequence[i];                    
    int actualButton = -1;    
    bool value = false;

    //Output debug information
    Serial.print("Correct button: ");
    setColourText(colourText, correctButton);       
    Serial.println(colourText);

    //Loop until player pressess a button.
    while(actualButton == -1)
    { 
      // Read each button in turn to see if the player has pressed it.
      for (int i = 0; i < 4; i++)   
      {     
          value = digitalRead(i + buttonOffSet);  
          if (value)
          {
            actualButton = i;
            playTone(actualButton);            
            while(value)                      
            { 
              value = digitalRead(i + buttonOffSet);             
              digitalWrite(i + offSet, value);
            }                      
          }          
      }      
    }
    delay(delayLength); //Button debounce, prevents it reading the same value twice.
    failed = (correctButton != actualButton); // Fail if they pressed the wrong button in the sequence  

    //Output debug information
    Serial.print("Actual button: ");
    setColourText(colourText, actualButton);    
    Serial.println(colourText);    
  }
  
  if(failed)
  {    
    lose();
  }
}

void lose()
{
  sequenceLength = 0;
  playTone(-1);    
  flashAll(5);
}

void flashAll(int times)
{  
  for(int i=0; i < times; i++)
  {
    for(int j=offSet; j < 4 + offSet; j++)
    {
      digitalWrite(j, HIGH);  
    }    
    delay(delayLength);
    for(int j=offSet; j < 4 + offSet; j++)
    {
      digitalWrite(j, LOW);  
    }  
    delay(delayLength);    
  }
}

// Plays the relevent tones for each colour, these aproximate the tones and colour mappings of the original 1980s simon toy.
// If you have wired the LEDS in a different order to red, green, yellow, blue then you might want to edit this accordingly.
void playTone(int colour)
{  
  switch(colour)
  {
    case 0:
    tone(buzzerPin, redTone, delayLength);
    break;
    case 1:
    tone(buzzerPin, greenTone, delayLength);
    break;
    case 2:
    tone(buzzerPin, yellowTone, delayLength);
    break;
    case 3:
    tone(buzzerPin, blueTone, delayLength);
    break;
    default:
    tone(buzzerPin, loseTone, delayLength);    
  }
}

// MAps the text to the LED colours for outputting to serial monitor.
// If you have wired the LEDS in a different order to red, green, yellow, blue then you might want to edit this accordingly.
void setColourText(char *textToSet, int pin)
{ 
  switch(pin)
  {
    case 0:
    strcpy(textToSet, "Red");           //LED Colour for pin 0
    break;
    case 1:
    strcpy(textToSet, "Green");         //LED Colour for pin 1    
    break;
    case 2:
    strcpy(textToSet, "Yellow");        //LED Colour for pin 2
    break;
    case 3:
    strcpy(textToSet, "Blue");          //LED Colour for pin 3
    break;
    default:
    strcpy(textToSet, "Error");        
  }    
}
