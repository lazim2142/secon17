#ifndef GLOBALS_H
#define GLOBALS_H

#include "Arduino.h"

// Stage Geoemtry *******************************
// This layer is the largest area, and  comprises over half
// of the playing surface (45” wide by 57” long), and contains
// the robot starting square and the locations of stages 1, 2 and 3.
// The starting square is 15”x15” and is located in the center of
// this space (15” from the inside of the long walls of the arena,
// and 21” from the inside of the short wall).
const float ARENA_LENGTH = 57;
const float ARENA_WIDTH = 45;
const float DIST_2_LONG_WALL = ARENA_LENGTH / 2;
const float DIST_2_SHORT_WALL = ARENA_WIDTH / 2;
const float ROBOT_RADIUS = 6.0;

// IR Sensor pins *******************************
// Clockwise from front of robot
const int IR1 = A0; 
const int IR2 = A1;
const int IR3 = A2;
const int IR4 = A3;
const int IR5 = A13;
const int IR6 = A14;
const int IR7 = A15;
const int IR8 = A12;

// Motor Pins ***********************************
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

namespace Stage1{
}

namespace Stage2{
  const int SOLENOID_PIN = 13;
  const int SERVO_PIN = 9;
  
  const int INIT_MICRO_SECONDS = 1700;
  const int ACTION_MICRO_SECONDS = 1500;
}

namespace Stage3{
  const int SERVO_PIN = 10;
  const int TURN_SPEED = 15;
  const int TURN_MILLI_SECONDS = 5050;
  const int DIR = 1;
}

namespace Stage4{
  const int GUN_PIN = 13;
}

int signof(float);

#endif
