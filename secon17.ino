#include "motion.h"
#include "ir_sensor.h"

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
//  motorsetup();
//  enableMotors();
  Serial.begin(9600);
}

void loop()
{
  updateSensors();  
  //printSensors();
  
  ir_front.printCalibration();
  //ir_front2.printCalibration();

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

void printSensors()
{
  ir_front.serialPrint();
  ir_front2.serialPrint();
  ir_right.serialPrint();
  ir_right2.serialPrint();
  ir_back.serialPrint();
  ir_back2.serialPrint();
  ir_left.serialPrint();
  ir_left2.serialPrint();
}


