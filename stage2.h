#include "ir_sensor.h"
#include "motion.h"
#include "magnetometer.h"
#include "globals.h"
#include <Servo.h>

// External references lead to secon17.ino
extern IRSensor ir_front_short, ir_front_long,
       ir_back_short, ir_back_long,
       ir_left_short, ir_left_long,
       ir_right_short, ir_right_long;

namespace Stage2
{
//HIT THE LIGHT-SABER
Servo servo;

void init() {
  pinMode(SOLENOID_PIN, OUTPUT);
  digitalWrite(SOLENOID_PIN, LOW);

  pinMode(SERVO_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  servo.writeMicroseconds(INIT_MICRO_SECONDS);
  
  Magnetometer::init();
}

enum {move_back, align_pos, detect_magnet, duel, done} state = move_back;
int transition_counter = 0;
int lightsaber_counter = 0;
unsigned long duel_start_time = 0;
bool perform()
{
  switch (state)
  {
    case move_back:
      {
        servo.writeMicroseconds(ACTION_MICRO_SECONDS);
        // Update relevant sensors
        ir_back_long.update();
        ir_back_short.update();

        // Move Back
        float error = ir_back_short.getInches() - 3;
        if (fabs(error) > 0.1) {
          Motion::goBack(max(1, fabs(map(error, 0, 7, 0, 100))) * signof(error));
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
        ir_right_long.update();

        // Move left/right
        float error = ir_right_long.getInches() - ARENA_WIDTH/2.0;
        if (fabs(error) > 0.1) {
          Motion::goRight(max(1, fabs(map(error, 0, 7, 0, 100))) *  signof(error));
          transition_counter = 0;
        }
        // Stop and transition if done
        else {
          Motion::stopMoving();
          if (++transition_counter >= 20) {
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
          
        if(Magnetometer::fieldDetected()) {
          ++lightsaber_counter;
          duel_start_time = millis();
          state = duel;
        }
        
        break;
      }
    case duel:
      {
        if(millis() - duel_start_time < 500)
          digitalWrite(SOLENOID_PIN, HIGH);
        else {
          state = detect_magnet;
          digitalWrite(SOLENOID_PIN, LOW);
          delay(2300);
        }
        break;
      }
    case done:
      {
        Motion::stopMoving();
        servo.writeMicroseconds(INIT_MICRO_SECONDS);
        return true;
      }
      break;
  }
  
  return false;
}

}
