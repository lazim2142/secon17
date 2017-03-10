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

// Step signal minimum high time
const int STEP_MICROSECONDS = 10000;

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

unsigned long M1_step_time;
unsigned long M2_step_time;
unsigned long M3_step_time;
unsigned long M4_step_time;

bool M1_step_level;
bool M2_step_level;
bool M3_step_level;
bool M4_step_level;

void setMotorSpeed(int motor, unsigned long s)
{
  int dir_pin, step_pin;
  unsigned long* last_step_time;
  bool* step_level;
  switch (motor)
  {
    case 1:
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

  if (s != 0)
  {
    // Set Direction
    if (s < 0)
      digitalWrite(dir_pin, HIGH);
    else
      digitalWrite(dir_pin, LOW);

    // Maintiain Step Pulse Timing
    unsigned long curr_time = micros();
<<<<<<< HEAD
    //Serial.println(*step_level);
=======
  //  Serial.println(*step_level);
>>>>>>> feef492e4fe55a229dac7fa88b72b3cb13ce2926
    if (curr_time - (*last_step_time) >= s)
    {
      if(*step_level)
      {
<<<<<<< HEAD
        //Serial.println("Setting Low");
=======
       // Serial.println("Setting Low");
>>>>>>> feef492e4fe55a229dac7fa88b72b3cb13ce2926
        digitalWrite(step_pin, LOW);    
        *step_level = false;
      }
      else
      {
        //Serial.println("Setting High");
        digitalWrite(step_pin, HIGH);
        *step_level = true;
      }
      //Serial.println(curr_time - (*last_step_time));
      *last_step_time = curr_time;
    }
  }
  else
    digitalWrite(step_pin, LOW);
}

// Proportional Control
float PK = 1.0;

// Angle offset of wheel axis from robot east
const float M1_OFFSET = 45.0 * M_PI / 180.0;
const float M2_OFFSET = 135.0 * M_PI / 180.0;
const float M3_OFFSET = 225.0 * M_PI / 180.0;
const float M4_OFFSET = 315.0 * M_PI / 180.0;

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



void align(int direc)
{
  switch (direc)
  {
    case 1:
      break;
    case 2:
  //  Serial.println(ir_right_short.getInches());
   // Serial.println(ir_right_long.getInches());
      if((ir_right_short.getInches() - ir_right_long.getInches()) > 0.1){
        setMotorSpeed(1,-1);
        setMotorSpeed(2,-1);
        setMotorSpeed(3,-1);
        setMotorSpeed(4,-1);
        Serial.println("counterclockwise");
      }

      else if((ir_right_short.getInches() - ir_right_long.getInches()) < -0.1){
        setMotorSpeed(1,1);
        setMotorSpeed(2,1);
        setMotorSpeed(3,1);
        setMotorSpeed(4,1);
        Serial.println("clockwise");
      }

      else{
        setMotorSpeed(1,0);
        setMotorSpeed(2,0);
        setMotorSpeed(3,0);
        setMotorSpeed(4,0);
      }
      break;
  }
}
}

