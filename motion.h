#ifndef MOTION_H
#define MOTION_H

// Clockwise dir-high
#include "Arduino.h"
#include "ir_sensor.h"

// Current pose
extern float x, y;
extern int orientation;
extern IRSensor ir_front_short;
extern IRSensor ir_front_long;
extern IRSensor ir_left_short;
extern IRSensor ir_left_long;
extern IRSensor ir_right_short;
extern IRSensor ir_right_long;
extern IRSensor ir_back_short;
extern IRSensor ir_back_long;

namespace Motion {

// M1 Constants - Motor X Ramps Pinouts
const int M1DPin = 40;
const int M1EPin = 36;
const int M1SPin = 38;

// M2 Constants - Motor Z Ramps Pinouts
const int M2DPin = 41;
const int M2EPin = 37;
const int M2SPin = 39;

// M3 Constants - Motor Y Ramps Pinouts
const int M3DPin = 35;
const int M3EPin = 31;
const int M3SPin = 33;

// M4 Constants - Motor E Ramps Pinouts
const int M4DPin = 34;
const int M4EPin = 30;
const int M4SPin = 32;

unsigned long M1_step_time;
unsigned long M2_step_time;
unsigned long M3_step_time;
unsigned long M4_step_time;

bool M1_step_level;
bool M2_step_level;
bool M3_step_level;
bool M4_step_level;

void setMotorSpeed(int motor, int spd)
{
  int dir_pin, step_pin;
  unsigned long* last_step_time;
  bool* step_level;
  switch (motor)
  {
    case 1:
      dir_pin = M1DPin;
      step_pin = M1SPin;
      last_step_time = &M1_step_time;
      step_level = &M1_step_level;
      break;
    case 2:
      dir_pin = M2DPin;
      step_pin = M2SPin;
      last_step_time = &M2_step_time;
      step_level = &M2_step_level;
      break;
    case 3:
      dir_pin = M3DPin;
      step_pin = M3SPin;
      last_step_time = &M3_step_time;
      step_level = &M3_step_level;
      break;
    case 4:
      dir_pin = M4DPin;
      step_pin = M4SPin;
      last_step_time = &M4_step_time;
      step_level = &M4_step_level;
      break;
  }

  if (spd != 0)
  {
    // Set Direction
    if (spd < 0)
      digitalWrite(dir_pin, HIGH);
    else
      digitalWrite(dir_pin, LOW);

    const unsigned long MAX_DELAY = 20000, MIN_DELAY = 2000;
    unsigned long s =  map(min(100, max(0, abs(spd))), 0, 100, MAX_DELAY, MIN_DELAY);

    // Maintiain Step Pulse Timing
    unsigned long curr_time = micros();
    if (curr_time - (*last_step_time) >= s)
    {
      if (*step_level)
      {
        digitalWrite(step_pin, LOW);
        *step_level = false;
      }
      else
      {
        digitalWrite(step_pin, HIGH);
        *step_level = true;
      }
      *last_step_time = curr_time;
    }
  }
  else
    digitalWrite(step_pin, LOW);
}

void goLeft(int spd)
{
  setMotorSpeed(1, spd);
  setMotorSpeed(2, -spd);
  setMotorSpeed(3, -spd);
  setMotorSpeed(4, spd);
}

void goRight(int spd)
{
  setMotorSpeed(1, -spd);
  setMotorSpeed(2, spd);
  setMotorSpeed(3, spd);
  setMotorSpeed(4, -spd);
}

void goBack(int spd)
{
  setMotorSpeed(1, -spd);
  setMotorSpeed(2, -spd);
  setMotorSpeed(3, spd);
  setMotorSpeed(4, spd);
}

void goFront(int spd)
{
  setMotorSpeed(1, spd);
  setMotorSpeed(2, spd);
  setMotorSpeed(3, -spd);
  setMotorSpeed(4, -spd);
}

void rotateRight(int spd)
{
  setMotorSpeed(1, spd);
  setMotorSpeed(2, spd);
  setMotorSpeed(3, spd);
  setMotorSpeed(4, spd);
}

void rotateLeft(int spd)
{
  setMotorSpeed(1, -spd);
  setMotorSpeed(2, -spd);
  setMotorSpeed(3, -spd);
  setMotorSpeed(4, -spd);
}

void stopMoving()
{
  setMotorSpeed(1, 0);
  setMotorSpeed(2, 0);
  setMotorSpeed(3, 0);
  setMotorSpeed(4, 0);
}

void motorsetup() {
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

void disableMotors()
{
  digitalWrite(M1EPin, HIGH);
  digitalWrite(M2EPin, HIGH);
  digitalWrite(M3EPin, HIGH);
  digitalWrite(M4EPin, HIGH);
}

void enableMotors()
{
  digitalWrite(M1EPin, LOW);
  digitalWrite(M2EPin, LOW);
  digitalWrite(M3EPin, LOW);
  digitalWrite(M4EPin, LOW);
}

enum dir {left, right, back};
bool align(dir drctn)
{
  return true;
  float error;
  switch (drctn)
  {
    case left:
      {
        ir_left_short.update();
        ir_left_long.update();
        float error = ir_left_short.getInches() - ir_left_long.getInches();
      }
      break;
    case right:
      {
        ir_right_short.update();
        ir_right_long.update();
        float error = ir_right_short.getInches() - ir_right_long.getInches();
      }
      break;
    case back:
      {
        ir_back_short.update();
        ir_back_long.update();
        float error = ir_back_short.getInches() - ir_back_long.getInches();
      }
      break;
  }

  if (error > 0.1)
    rotateLeft(10);
  else if (error < -0.1)
    rotateRight(10);
  else
  {
    stopMoving();
    return true;
  }
  
  return false;
}
}
#endif
