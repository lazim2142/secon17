#include "motion.h"
#include "ir_sensor.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"
#include <Wire.h>
#include <Servo.h>

void setup()
{
  Stage1::init();
  Stage2::init();
  Stage3::init();
  Stage4::init();
  
  Motion::motorsetup();
  Motion::enableMotors();
  Motion::stopMoving();
  
  Serial.begin(9600);
}

void loop()
{
  if(Stage1::perform())
    if(Stage2::perform())
      if(Stage3::perform())
        if(Stage4::perform());
}
