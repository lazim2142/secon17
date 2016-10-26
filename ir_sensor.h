#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

#include "Arduino.h"

class IRSensor
{
public:
  IRSensor(int pin);
  void update();
  int getDist();
  int getAnalogReading();
private:
  int pin;
  int r;
};

#endif



