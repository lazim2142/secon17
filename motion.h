// Clockwise dir-high
#include "Arduino.h"

const int stepdelay = 1000;
int speeddelay = 1000;

// M1 Constants - Motor Z Ramps Pinouts
const int M1DPin = 48;
const int M1EPin = 62;
const int M1SPin = 46;

// M2 Constants - Motor X Ramps Pinouts
const int M2DPin = 55;
const int M2EPin = 38;
const int M2SPin = 54;

// M3 Constants - Motor Y Ramps Pinouts
const int M3DPin = 61;
const int M3EPin = 56;
const int M3SPin = 60;

// M4 Constants - Motor E Ramps Pinouts
const int M4DPin = 28;
const int M4EPin = 24;
const int M4SPin = 26;

void motorsetup(){

  // Set up all pin modes
  // Motor 1
  pinMode(M1DPin, OUTPUT);
  pinMode(M1EPin, OUTPUT);
  pinMode(M1SPin, OUTPUT);
  
  // Motor 2
  pinMode(M2DPin, OUTPUT);
  pinMode(M2EPin, OUTPUT);
  pinMode(M2SPin, OUTPUT);
  
  // Motor 3
  pinMode(M3DPin, OUTPUT);
  pinMode(M3EPin, OUTPUT);
  pinMode(M3SPin, OUTPUT);
  
  // Motor 4
  pinMode(M4DPin, OUTPUT);
  pinMode(M4EPin, OUTPUT);
  pinMode(M4SPin, OUTPUT);
}


void forward()
{
  // Motor 2 - C-Clockwise Step     // Motor 1 - Clockwise Step
  // Motor 3 - C-Clockwise Step     // Motor 4 - Clockwise Step

  // Set Directions
  digitalWrite(M1DPin, HIGH);      // Clockwise
  digitalWrite(M2DPin, LOW);       // C-Clockwise
  digitalWrite(M3DPin, LOW);       // C-Clockwise
  digitalWrite(M4DPin, HIGH);      // Clockwise  
  
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M2SPin, LOW);
  digitalWrite(M3SPin, LOW);  
  digitalWrite(M4SPin, LOW);  
  
  delayMicroseconds(stepdelay);
  
  // High
  digitalWrite(M1SPin, HIGH);
  digitalWrite(M2SPin, HIGH);
  digitalWrite(M3SPin, HIGH);  
  digitalWrite(M4SPin, HIGH);  
  
  delayMicroseconds(stepdelay);
 
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M2SPin, LOW);
  digitalWrite(M3SPin, LOW);  
  digitalWrite(M4SPin, LOW);  
  
  delayMicroseconds(speeddelay);
}

void backward()
{
  // Motor 2 - Clockwise Step       // Motor 1 - C-Clockwise Step
  // Motor 3 - Clockwise Step       // Motor 4 - C-Clockwise Step

  // Set Directions
  digitalWrite(M1DPin, LOW);        // C-Clockwise
  digitalWrite(M2DPin, HIGH);       // Clockwise
  digitalWrite(M3DPin, HIGH);       // Clockwise
  digitalWrite(M4DPin, LOW);        // C-Clockwise  
  
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M2SPin, LOW);
  digitalWrite(M3SPin, LOW);  
  digitalWrite(M4SPin, LOW);  
  
  delayMicroseconds(stepdelay);
  
  // High
  digitalWrite(M1SPin, HIGH);
  digitalWrite(M2SPin, HIGH);
  digitalWrite(M3SPin, HIGH);  
  digitalWrite(M4SPin, HIGH);  
  
  delayMicroseconds(stepdelay);
  
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M2SPin, LOW);
  digitalWrite(M3SPin, LOW);  
  digitalWrite(M4SPin, LOW);  

  delayMicroseconds(speeddelay);
}

void left()
{
  // Motor 2 - Clockwise Step       // Motor 1 - Clockwise Step
  // Motor 3 - C-Clockwise Step     // Motor 4 - C-Clockwise Step

  // Set Directions
  digitalWrite(M1DPin, HIGH);      // Clockwise
  digitalWrite(M2DPin, HIGH);      // Clockwise
  digitalWrite(M3DPin, LOW);       // C-Clockwise
  digitalWrite(M4DPin, LOW);       // C-Clockwise
  
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M2SPin, LOW);
  digitalWrite(M3SPin, LOW);  
  digitalWrite(M4SPin, LOW);  
  
  delayMicroseconds(stepdelay);
  
  // High
  digitalWrite(M1SPin, HIGH);
  digitalWrite(M2SPin, HIGH);
  digitalWrite(M3SPin, HIGH);  
  digitalWrite(M4SPin, HIGH);  
  
  delayMicroseconds(stepdelay);
  
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M2SPin, LOW);
  digitalWrite(M3SPin, LOW);  
  digitalWrite(M4SPin, LOW);  
  
  delayMicroseconds(speeddelay);
}

void right()
{
  // Motor 2 - C-Clockwise Step       // Motor 1 - C-Clockwise Step
  // Motor 3 - Clockwise Step         // Motor 4 - Clockwise Step

  // Set Directions
  digitalWrite(M1DPin, LOW);      // C-Clockwise
  digitalWrite(M2DPin, LOW);      // C-Clockwise
  digitalWrite(M3DPin, HIGH);       // Clockwise
  digitalWrite(M4DPin, HIGH);       // Clockwise
  
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M2SPin, LOW);
  digitalWrite(M3SPin, LOW);  
  digitalWrite(M4SPin, LOW);  
  
  delayMicroseconds(stepdelay);
  
  // High
  digitalWrite(M1SPin, HIGH);
  digitalWrite(M2SPin, HIGH);
  digitalWrite(M3SPin, HIGH);  
  digitalWrite(M4SPin, HIGH);  
  
  delayMicroseconds(stepdelay);
  
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M2SPin, LOW);
  digitalWrite(M3SPin, LOW);  
  digitalWrite(M4SPin, LOW);  
  
  delayMicroseconds(speeddelay);  
}

void forwardLeft()
{
  // Motor 2 - Disabled                 // Motor 1 - Clockwise Step
  // Motor 3 - C-Clockwise Step         // Motor 4 - Disabled

  // Set Directions
  digitalWrite(M1DPin, HIGH);      // Clockwise
  digitalWrite(M3DPin, LOW);       // C- Clockwise
  
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M3SPin, LOW);  
  
  delayMicroseconds(stepdelay);
  
  // High
  digitalWrite(M1SPin, HIGH);
  digitalWrite(M3SPin, HIGH);  

  
  delayMicroseconds(stepdelay);
  
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M3SPin, LOW); 
  
  delayMicroseconds(speeddelay);
}

void forwardRight()
{
  // Motor 2 - C-Clockwise step     // Motor 1 - Disabled
  // Motor 3 - Disabled             // Motor 4 - Clockwise step

  // Set Directions    
  digitalWrite(M2DPin, LOW);         // C-Clockwise     
  digitalWrite(M4DPin, HIGH);        // Clockwise
  
  // Low 
  digitalWrite(M2SPin, LOW); 
  digitalWrite(M4SPin, LOW);  
  
  delayMicroseconds(stepdelay);
  
  // High
  digitalWrite(M2SPin, HIGH); 
  digitalWrite(M4SPin, HIGH);  
  
  delayMicroseconds(stepdelay);
  
  // Low 
  digitalWrite(M2SPin, LOW); 
  digitalWrite(M4SPin, LOW); 
  
  delayMicroseconds(speeddelay);
}

void backwardLeft()
{
  // Motor 2 - Clockwise step       // Motor 1 - Disabled
  // Motor 3 - Disabled             // Motor 4 - C-Clockwise step

  // Set Directions    
  digitalWrite(M2DPin, HIGH);         // Clockwise     
  digitalWrite(M4DPin, LOW);          // C-Clockwise
  
  // Low 
  digitalWrite(M2SPin, LOW);
  digitalWrite(M4SPin, LOW);  
  
  delayMicroseconds(stepdelay);
  
  // High
  digitalWrite(M2SPin, HIGH);  
  digitalWrite(M4SPin, HIGH);  
  
  delayMicroseconds(stepdelay);
  
  // Low 
  digitalWrite(M2SPin, LOW); 
  digitalWrite(M4SPin, LOW); 
  
  delayMicroseconds(speeddelay);
}

void backwardRight()
{
  // Motor 2 - Disabled             // Motor 1 - C-Clockwise
  // Motor 3 - Clockwise            // Motor 4 - Disabled

  // Set Directions
  digitalWrite(M1DPin, LOW);           // C-Clockwise      
  digitalWrite(M3DPin, HIGH);          // Clockwise        
  
  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M3SPin, LOW);    
  
  delayMicroseconds(stepdelay);
  
  // High
  digitalWrite(M1SPin, HIGH);
  digitalWrite(M3SPin, HIGH);   
  
  delayMicroseconds(stepdelay);
  
  // Low 
  digitalWrite(M2SPin, LOW); 
  digitalWrite(M4SPin, LOW); 
  
  delayMicroseconds(speeddelay);
}

void disableMotors()
{
  digitalWrite(M1EPin, 1);
  digitalWrite(M2EPin, 1);
  digitalWrite(M3EPin, 1);
  digitalWrite(M4EPin, 1);
}

void enableMotors()
{
  digitalWrite(M1EPin, 0);
  digitalWrite(M2EPin, 0);
  digitalWrite(M3EPin, 0);
  digitalWrite(M4EPin, 0);
}

