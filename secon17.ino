#include "motion.h"
#include "ir_sensor.h"

IRSensor ir_front(A3);
IRSensor ir_left(A4);
IRSensor ir_right(A5);
IRSensor ir_back(A9);

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
  ir_back.update();
  ir_left.update();
  ir_right.update();
}

