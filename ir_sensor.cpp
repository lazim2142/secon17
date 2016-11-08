#include "ir_sensor.h"

IRSensor::IRSensor(int pin) : pin(pin)
{}

void IRSensor::update()
{
  r = analogRead(pin);
}

int IRSensor::getAnalogReading()
{
  return r;
}

double IRSensor::getDist()
{
  return min(20, max(0, 0.000000000952 * r * r * r * r
                     - 0.000001737 * r * r * r
                     + 0.001169 * r * r
                     - 0.356 * r
                     + 47.227));
}
