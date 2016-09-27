#include <Servo.h>
#include "sensors.h";
#include "motors.h";
#include "nerfgunfire.h";
#include "calibrate.h"


void setup () {
  motorsetup();

  // Enable motors to keep from moving around
  digitalWrite(M1EPin, LOW);
  digitalWrite(M2EPin, LOW);
  digitalWrite(M3EPin, LOW);
  digitalWrite(M4EPin, LOW);
}

void loop() {
  north();
}


