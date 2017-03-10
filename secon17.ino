#include "motion.h"
#include "ir_sensor.h"
#include "localization.h"

IRSensor ir_front_short(IR1);
IRSensor ir_front_long(IR2);
IRSensor ir_right_short(IR3);
IRSensor ir_right_long(IR4);
IRSensor ir_back_short(IR6);
IRSensor ir_back_long(IR5);
IRSensor ir_left_short(IR7);
IRSensor ir_left_long(IR8);

float x, y;
int orientation = 0;

void setup ()
{
  Motion::motorsetup();
  Motion::enableMotors();
  Serial.begin(9600);
}

void loop()
{
  //IRSensor::updateAllSensors();
  //Serial.println(ir_back_long.getInches());
  //IRSensor::printSensors();
  
  if(millis() > 3000)
  {
    Motion::disableMotors();
    return;
  }
  
  Motion::setMotorSpeed(1, 50000);
  //Motion::setMotorSpeed(2, 1300);
  //Motion::setMotorSpeed(3, 1000);
  //Motion::setMotorSpeed(4, 1000);
  
  //Localization::updatePose();  
  //Motion::goToPosition(0, 0);
}
