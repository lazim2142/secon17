//#include "ir_sensor.h"
//#include "motion.h"
//#include <Servo.h>
//
//// External references lead to secon17.ino
//extern IRSensor ir_front_short, ir_front_long,
//       ir_back_short, ir_back_long,
//       ir_left_short, ir_left_long,
//       ir_right_short, ir_right_long;
//
//namespace Stage3
//{
///*
//This layer is the largest area, and	comprises over half
//of the playing surface (45” wide by 57” long), and contains
//the robot starting square and the locations of stages 1, 2 and 3.
//The starting square is 15”x15” and is located in the center of
//this space (15” from the inside of the long walls of the arena,
//and	21” from the inside of the short wall).
//*/
//
//const float ARENA_LENGTH = 57;
//const float ARENA_WIDTH = 45;
//const float DIST_2_LONG_WALL = ARENA_LENGTH / 2;
//const float DIST_2_SHORT_WALL = ARENA_WIDTH / 2;
//const float ROBOT_RADIUS = 6.0;
//const int SERVO_PIN = 9;
//Servo servo;
//
//int signof(float f)
//{
//  return (f > 0)-(f < 0); 
//}
//
//int speed2ms(int spd)
//{
//  const int zero_ms = 1530;
//  const int max_ms = 1700;
//  return map(spd, 0, 100, zero_ms, max_ms);
//}
//
//void init()
//{
//  pinMode(SERVO_PIN, OUTPUT);
//  servo.attach(SERVO_PIN);
//}
//
//enum {move_left, align_pos, task, done} state = move_left;
//int transition_counter = 0;
//bool goToStage1()
//{
//  switch (state)
//  {
//    case move_left:
//      {
//        // Update relevant sensors
//        ir_left_long.update();
//        ir_right_short.update();
//
//        // Move Right
//        float dist_2_right_wall = ARENA_WIDTH - ir_left_long.getInches() - 2 * ROBOT_RADIUS;
//        float error = dist_2_right_wall - 1.0;
//        if (fabs(error) > 0.1)
//        {
//          Motion::goRight(max(1, fabs(map(error, 0, 7, 0, 100))) * signof(error));
//          transition_counter = 0;
//        }
//        // Stop and transition if done
//        else
//        {
//          Motion::stopMoving();
//          if (++transition_counter >= 20)
//          {
//            transition_counter = 0;
//            state = align_pos;
//          }
//        }
//
//        break;
//      }
//    case align_pos:
//      {
//        // Update relevant sensors
//        ir_back_long.update();
//
//        // Move Back/Forward
//        float error = 20.0 - ir_back_long.getInches();
//        if (fabs(error) > 0.1)
//        {
//          Motion::goBack(max(1, fabs(map(error, 0, 7, 0, 100))) *  signof(error));
//          transition_counter = 0;
//        }
//        // Stop and transition if done
//        else
//        {
//          Motion::stopMoving();
//          if (++transition_counter >= 20)
//          {
//            transition_counter = 0;
//            state = task;
//          }
//        }
//
//        break;
//      }
//    case task:
//      {
//        state = done;
//        break;
//      }
//    case done:
//      {
//        Motion::stopMoving();
//        return true;
//      }
//      break;
//
//  }
//  return false;
//}
//
//void goToStage2()
//{
//  // Move Back
//}
//
//enum {travel, align, finetune, done} stage3_state = travel;
//void goToStage3()
//{
//  // Get left sensor readings
//  ir_left_long.update();
//  ir_left_short.update();
//
//  switch (stage3_state)
//  {
//    case travel:
//      {
//        // Move Left
//        float error = ir_left_short.getInches() - 4.0;
//        if (fabs(error) > 0.1)
//          Motion::goLeft(map(error, 0, 3, 0, 100));
//        else
//          Motion::stopMoving();
//        break;
//      }
//    case align:
//      break;
//    case finetune:
//      break;
//    case done:
//      Motion::stopMoving();
//      break;
//  }
//}
//
//}
