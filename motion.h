#ifndef MOTION_H
#define MOTION_H

#include "Arduino.h"
#include "ir_sensor.h"
#include "globals.h"

namespace Motion {
void goLeft(int spd);
void goRight(int spd);
void goBack(int spd);
void goFront(int spd);

void rotateRight(int spd);
void rotateLeft(int spd);

void setMotorSpeed(int motor, int spd);
void stopMoving();

void motorsetup();
void disableMotors();
void enableMotors();

enum dir {left, right, back};
bool align(dir drctn);
}
#endif
