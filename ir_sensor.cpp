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

double IRSensor::getDist()
{
  int r = running_median.getMedian();
  return min(20, max(0, 0.000000000952 * r * r * r * r
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

