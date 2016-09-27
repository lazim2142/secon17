#include "Arduino.h"

const int gunpin = 28;


void nerfgunfire () {

  digitalWrite(gunpin, LOW);  
  delayMicroseconds(10);
  digitalWrite(gunpin, HIGH);
  delay (300);             //Milliseconds
  digitalWrite(gunpin, LOW);  
  
}
