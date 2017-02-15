#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

#include "Arduino.h"
#include "RunningMedian.h"

// Clockwise from front of robot
const int IR1 = A0; 
const int IR2 = A1;
const int IR3 = A2;
const int IR4 = A3;
const int IR5 = A13;
const int IR6 = A14;
const int IR7 = A15;
const int IR8 = A12; 

class IRSensor
{
public:
  IRSensor(int pin);
  void update();
  double getDist();
  int getAnalogReading();
  void serialPrint();
  void printCalibration();
private:
  const int MEDIAN_WINDOW = 25;
  RunningMedian running_median; 
  int pin;
};

#endif



