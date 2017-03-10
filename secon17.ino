#include "motion.h"
#include "ir_sensor.h"
#include "localization.h"

IRSensor ir_front_short(IR1);
IRSensor ir_front_long(IR2);
IRSensor ir_left_short(IR7);
IRSensor ir_left_long(IR8);
IRSensor ir_right_short(IR3);
IRSensor ir_right_long(IR4);
IRSensor ir_back_short(IR5);
IRSensor ir_back_long(IR6);

float x, y;
int orientation = 0;

void setup ()
{
  Motion::motorsetup();
  //Motion::enableMotors();
  Motion::disableMotors();
  Serial.begin(9600);
}

void loop()
{
  IRSensor::updateAllSensors();
  //Localization::updatePose();
  //Motion::goToPosition(0, 0);
  Motion::align(2);
}




