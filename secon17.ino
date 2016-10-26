#include "motion.h"
#include "ir_sensor.h"

IRSensor ir_front(A3);
IRSensor ir_left(A4);
IRSensor ir_right(A5);
IRSensor ir_back(A9);

void setup ()
{
  motorsetup();
  disablemotors();
  Serial.begin(9600);
}

void loop()
{
  ir_front.update();
  ir_back.update();
  ir_left.update();
  ir_right.update();
  //Serial.println(ir_front.getDist());
  Serial.println(ir_back.getDist());
    
}
