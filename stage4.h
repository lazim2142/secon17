#include "ir_sensor.h"
#include "motion.h"

// External references lead to secon17.ino
extern IRSensor ir_front_short, ir_front_long,
       ir_back_short, ir_back_long,
       ir_left_short, ir_left_long,
       ir_right_short, ir_right_long;

namespace Stage4
{
// GET CODE FOR STAGE 3
const float ARENA_LENGTH = 57;
const float ARENA_WIDTH = 45;
const float DIST_2_LONG_WALL = ARENA_LENGTH / 2;
const float DIST_2_SHORT_WALL = ARENA_WIDTH / 2;
const float ROBOT_RADIUS = 6.0;

const int GUN_PIN = 13;

int signof(float f) {
  return (f > 0) - (f < 0);
}

enum {move_center, align_pos, fire, done} state = move_center;
int transition_counter = 0;

void init(){
  pinMode(GUN_PIN, OUTPUT);
  //digitalWrite(GUN_PIN, LOW);
}

bool perform() {
  switch (state) {
    case move_center:
      {
        // Update relevant sensors
        ir_left_long.update();
        ir_right_short.update();

        // Move Right
        float dist_2_right_wall = ARENA_WIDTH - ir_left_long.getInches() - 2 * ROBOT_RADIUS;
        float error = dist_2_right_wall - (DIST_2_LONG_WALL - ROBOT_RADIUS);
        if (fabs(error) > 0.1) {
          Motion::goRight(max(1, fabs(map(error, 0, 7, 0, 100))) * signof(error));
          transition_counter = 0;
        }
        // Stop and transition if done
        else {
          Motion::stopMoving();
          if (++transition_counter >= 20) {
            transition_counter = 0;
            state = align_pos;
          }
        }

        break;
      }
    case align_pos:
      {
        // Update relevant sensors
        ir_back_long.update();

        // Move Back/Forward
        float error = 20.0 - ir_back_long.getInches();
        if (fabs(error) > 0.1) {
          Motion::goBack(max(1, fabs(map(error, 0, 7, 0, 100))) *  signof(error));
          transition_counter = 0;
        }
        // Stop and transition if done
        else {
          Motion::stopMoving();
          if (++transition_counter >= 20) {
            transition_counter = 0;
            state = fire;
          }
        }

        break;
      }
    case fire:
      {
        digitalWrite(GUN_PIN, HIGH);
        delay(3000);
        digitalWrite(GUN_PIN, LOW);
        state = done;
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
