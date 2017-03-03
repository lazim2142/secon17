// Clockwise dir-high
#include "Arduino.h"

// Current pose
extern float x, y;
extern int orientation;

namespace Motion {

// Step signal minimum high time
const int STEP_MICROSECONDS = 1;

// M1 Constants - Motor Z Ramps Pinouts
const int M1DPin = 41;
const int M1EPin = 37;
const int M1SPin = 39;

// M2 Constants - Motor X Ramps Pinouts
const int M2DPin = 40;
const int M2EPin = 36;
const int M2SPin = 38;

// M3 Constants - Motor Y Ramps Pinouts
const int M3DPin = 35;
const int M3EPin = 31;
const int M3SPin = 33;

// M4 Constants - Motor E Ramps Pinouts
const int M4DPin = 34;
const int M4EPin = 30;
const int M4SPin = 32;

// Angle offset of wheel axis from robot east
const float M1_OFFSET = 45.0 * M_PI / 180.0;
const float M2_OFFSET = 135.0 * M_PI / 180.0;
const float M3_OFFSET = 225.0 * M_PI / 180.0;
const float M4_OFFSET = 315.0 * M_PI / 180.0;

// Proportional Control
float PK = 1.0;

void setMotorSpeed(int motor, int s)
{
  int dir_pin, speed_pin;
  switch (motor)
  {
    case 1:
      dir_pin = M1DPin;
      speed_pin = M1SPin;
    case 2:
      dir_pin = M2DPin;
      speed_pin = M2SPin;
    case 3:
      dir_pin = M2DPin;
      speed_pin = M2SPin;
    case 4:
      dir_pin = M2DPin;
      speed_pin = M2SPin;
  }

  if (s != 0)
  {
    // Set Direction
    if (s < 0)
      digitalWrite(dir_pin, HIGH);
    else
      digitalWrite(dir_pin, LOW);

    // Set Speed
    digitalWrite(speed_pin, HIGH);
    delayMicroseconds(STEP_MICROSECONDS);
    digitalWrite(speed_pin, LOW);
    delayMicroseconds(max(0, min(1000, s)));
  }
  else
    digitalWrite(speed_pin, LOW);
}

void goToPosition(float x_target, float y_target)
{
  // Errors
  float x_error = x_target - x;
  float y_error = y_target - y;

  // Proportional Control
  float x_vel = x_error * PK;
  float y_vel = y_error * PK;

  // Robot Frame Velocities
  float ang = orientation * M_PI / 180.0;
  float y_vel_robot = cos(ang) * x_vel + sin(ang) * y_vel;
  float x_vel_robot = sin(ang) * x_vel - cos(ang) * y_vel;

  // Wheel Velocities
  float m1 =  (cos(M1_OFFSET) * y_vel_robot - sin(M1_OFFSET) * x_vel_robot);
  float m2 = -(cos(M2_OFFSET) * y_vel_robot - sin(M2_OFFSET) * x_vel_robot);
  float m3 = -(cos(M3_OFFSET) * y_vel_robot - sin(M3_OFFSET) * x_vel_robot);
  float m4 =  (cos(M4_OFFSET) * y_vel_robot - sin(M4_OFFSET) * x_vel_robot);

  // Actuate
  setMotorSpeed(1, m1);
  setMotorSpeed(2, m2);
  setMotorSpeed(3, m3);
  setMotorSpeed(4, m4);
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

}

