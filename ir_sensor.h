#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

#include "Arduino.h"
#include "globals.h"
#include "RunningMedian.h"

class IRSensor
{
public:
  IRSensor(int pin);
  void update();
  double getInches();
  int getAnalogReading();
  void serialPrint();
  void printCalibration();
  static void updateAllSensors();
  static void printSensors();
  
private:
  const int MEDIAN_WINDOW = 25;
  RunningMedian running_median;
  int pin;
};

#endif



