#include "motion.h"
#include "ir_sensor.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "magnetometer.h"
#include <Wire.h>
#include <Servo.h>

IRSensor ir_front_short(IR1);
IRSensor ir_front_long(IR2);
IRSensor ir_right_short(IR4);
IRSensor ir_right_long(IR3);
IRSensor ir_back_short(IR6);
IRSensor ir_back_long(IR5);
IRSensor ir_left_short(IR8);
IRSensor ir_left_long(IR7);

float x, y;
int orientation = 0;

void setup()
{
  Stage2::init();
  //Motion::motorsetup();
  //Motion::enableMotors();
//  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  Stage2::perform();
//  digitalWrite(13, LOW);
}
