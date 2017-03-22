#include "ir_sensor.h"
#include "motion.h"
#include "magnetometer.h"

// External references lead to secon17.ino
extern IRSensor ir_front_short, ir_front_long,
       ir_back_short, ir_back_long,
       ir_left_short, ir_left_long,
       ir_right_short, ir_right_long;

namespace Stage2
{
/*
This layer is the largest area, and	comprises over half
of the playing surface (45” wide by 57” long), and contains
the robot starting square and the locations of stages 1, 2 and 3.
The starting square is 15”x15” and is located in the center of
this space (15” from the inside of the long walls of the arena,
and	21” from the inside of the short wall).
*/

const float ARENA_LENGTH = 57;
const float ARENA_WIDTH = 45;
const float ROBOT_RADIUS = 6.0;
const int GUN_PIN = 13;

int signof(float f)
{
  return (f > 0)-(f < 0); 
}

void init()
{
  pinMode(GUN_PIN, OUTPUT);
  digitalWrite(GUN_PIN, LOW);
  Magnetometer::init();
}

enum {move_back, align_pos, detect_magnet, fire, done} state = detect_magnet;
int transition_counter = 0;
int lightsaber_counter = 0;
unsigned long fire_start_time = 0;
bool perform()
{
  switch (state)
  {
    case move_back:
      {
        // Update relevant sensors
        ir_back_long.update();
        ir_back_short.update();

        // Move Back
        float error = ir_back_short.getInches() - 3;
        if (fabs(error) > 0.1)
        {
          Motion::goBack(max(1, fabs(map(error, 0, 7, 0, 100))) * signof(error));
          transition_counter = 0;
        }
        // Stop and transition if done
        else
        {
          Motion::stopMoving();
          if (++transition_counter >= 20)
          {
            transition_counter = 0;
            state = align_pos;
          }
        }

        break;
      }
    case align_pos:
      {
        // Update relevant sensors
        ir_right_long.update();

        // Move left/right
        float error = ir_right_long.getInches() - ARENA_WIDTH/2.0;
        if (fabs(error) > 0.1)
        {
          Motion::goRight(max(1, fabs(map(error, 0, 7, 0, 100))) *  signof(error));
          transition_counter = 0;
        }
        // Stop and transition if done
        else
        {
          Motion::stopMoving();
          if (++transition_counter >= 20)
          {
            transition_counter = 0;
            
            state = detect_magnet;
          }
        }

        break;
      }
    case detect_magnet:
      {
        if(lightsaber_counter >= 4)
          state = done;
          
        if(Magnetometer::fieldDetected())
        {
          ++lightsaber_counter;
          fire_start_time = millis();
          state = fire;
        }
        
        break;
      }
    case fire:
      {
        if(millis() - fire_start_time < 500)
          digitalWrite(GUN_PIN, HIGH);
        else
        {
          state = detect_magnet;
          digitalWrite(GUN_PIN, LOW);
          delay(2300);
        }
        break;
      }
    case done:
      {
        Motion::stopMoving();
        return true;
      }
      break;
  }
  
  return false;
}

}
