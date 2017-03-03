#include "ir_sensor.h"

IRSensor::IRSensor(int pin) : pin(pin), running_median(RunningMedian(MEDIAN_WINDOW))
{
}

void IRSensor::update()
{
  running_median.add(analogRead(pin));
}

int IRSensor::getAnalogReading()
{
  return running_median.getMedian();
}

double IRSensor::getInches()
{
  int r = running_median.getMedian();
  return min(2, max(0, 0.000000000952 * r * r * r * r
                         - 0.000001737 * r * r * r
                         + 0.001169 * r * r
                         - 0.356 * r
                         + 47.227));
}

void IRSensor::serialPrint()
{
  Serial.print(running_median.getMedian());
  Serial.print("\t");
}

void IRSensor::printCalibration()
{
  if (Serial.read() == ' ')
  {
    Serial.println(running_median.getMedian());
  }
}

// External references lead back to secon17.ino
extern IRSensor ir_front_short, ir_front_long,
       ir_back_short, ir_back_long,
       ir_left_short, ir_left_long,
       ir_right_short, ir_right_long;

void IRSensor::updateAllSensors()
{
  ir_front_short.update();
  ir_front_long.update();
  ir_back_short.update();
  ir_back_long.update();
  ir_left_short.update();
  ir_left_long.update();
  ir_right_short.update();
  ir_right_long.update();
}

void IRSensor::printSensors()
{
  ir_front_short.serialPrint();
  ir_front_long.serialPrint();
  ir_right_short.serialPrint();
  ir_right_long.serialPrint();
  ir_back_short.serialPrint();
  ir_back_long.serialPrint();
  ir_left_short.serialPrint();
  ir_left_long.serialPrint();
}

