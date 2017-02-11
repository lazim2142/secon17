#include "motion.h"
#include "ir_sensor.h"

const int IR1 = 28;
const int IR2 = 26;
const int IR3 = 24;
const int IR4 = 22;
const int IR5 = A3;
const int IR6 = A2;
const int IR7 = A1;
const int IR8 = A0;

IRSensor ir_front(IR1);
IRSensor ir_front2(IR2);
IRSensor ir_left(IR7);
IRSensor ir_left2(IR8);
IRSensor ir_right(IR3);
IRSensor ir_right2(IR4);
IRSensor ir_back(IR5);
IRSensor ir_back2(IR6);


void setup ()
{
  motorsetup();
  enableMotors();
  Serial.begin(9600);
}

void loop()
{
  updateSensors();
  Serial.println(ir_front.getDist());
  forward();
//  if(ir_front.getDist() > 7)
//    forward();
//  if (ir_front.getDist() < 5)
//    backward();
}

void updateSensors()
{
  ir_front.update();
  ir_front2.update();
  ir_back.update();
  ir_back2.update();
  ir_left.update();
  ir_left2.update();
  ir_right.update();
  ir_right2.update();
}


