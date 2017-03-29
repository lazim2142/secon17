#include "ir_sensor.h"
#include "motion.h"
#include <Servo.h>

// External references lead to secon17.ino
extern IRSensor ir_front_short, ir_front_long,
       ir_back_short, ir_back_long,
       ir_left_short, ir_left_long,
       ir_right_short, ir_right_long;

extern int Stage1::code_array[5];

namespace Stage3
{
// OUTPUT CODE FROM STAGE 1

const float ARENA_LENGTH = 57;
const float ARENA_WIDTH = 45;
const float DIST_2_LONG_WALL = ARENA_LENGTH / 2;
const float DIST_2_SHORT_WALL = ARENA_WIDTH / 2;
const float ROBOT_RADIUS = 6.0;

const int SERVO_PIN = 10;
Servo servo;

int signof(float f) {
  return (f > 0) - (f < 0);
}

unsigned long rot_start_time = 0;
const int TURN_SPEED = 15;
const int TURN_MILLI_SECONDS = 5050;
const int DIR = 1;
int speed2ms(int spd) {
  const int zero_ms = 1530;
  const int max_ms = 1700;
  return map(spd, 0, 100, zero_ms, max_ms);
}

void init() {
  pinMode(SERVO_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  servo.writeMicroseconds(speed2ms(0));
}

enum {move_left, align_pos, pad1, pad2, pad3, pad4, pad5, done} state = move_left;
int transition_counter = 0;
bool perform() {
  switch (state) {
    case move_left:
      {
        // Update relevant sensors
        ir_right_long.update();
        ir_left_short.update();

        // Move Left
        float dist_2_left_wall = ARENA_WIDTH - ir_right_long.getInches() - 2 * ROBOT_RADIUS;
        float error = dist_2_left_wall - 1.0;
        if (fabs(error) > 0.1) {
          Motion::goLeft(max(1, fabs(map(error, 0, 7, 0, 100))) * signof(error));
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
            rot_start_time = millis();
            state = pad1;
          }
        }

        break;
      }
    case pad1:
      {
        int num_turns = Stage1::code_array[0];
        if (millis() - rot_start_time < num_turns * TURN_MILLI_SECONDS)
          servo.writeMicroseconds(speed2ms(15*DIR));
        else {
          rot_start_time = millis();
          servo.writeMicroseconds(speed2ms(0));
          state = pad2;
        }
        break;
      }
    case pad2:
      {
        int num_turns = Stage1::code_array[1];
        if (millis() - rot_start_time < num_turns * TURN_MILLI_SECONDS)
          servo.writeMicroseconds(speed2ms(-15*DIR));
        else {
          rot_start_time = millis();
          servo.writeMicroseconds(speed2ms(0));
          state = pad3;
        }
        break;
      }
    case pad3:
      {
        int num_turns = Stage1::code_array[2];
        if (millis() - rot_start_time < num_turns * TURN_MILLI_SECONDS)
          servo.writeMicroseconds(speed2ms(15*DIR));
        else {
          servo.writeMicroseconds(speed2ms(0));
          state = pad4;
        }
        break;
      }
    case pad4:
      {
        int num_turns = Stage1::code_array[3];
        if (millis() - rot_start_time < num_turns * TURN_MILLI_SECONDS)
          servo.writeMicroseconds(speed2ms(-15*DIR));
        else {
          rot_start_time = millis();
          servo.writeMicroseconds(speed2ms(0));
          state = pad5;
        }
        break;
      }
    case pad5:
      {
        int num_turns = Stage1::code_array[4];
        if (millis() - rot_start_time < num_turns * TURN_MILLI_SECONDS)
          servo.writeMicroseconds(speed2ms(15*DIR));
        else {
          rot_start_time = millis();
          servo.writeMicroseconds(speed2ms(0));
          state = done;
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
