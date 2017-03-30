#include "ir_sensor.h"

IRSensor ir_front_short(IR1);
IRSensor ir_front_long(IR2);
IRSensor ir_right_short(IR4);
IRSensor ir_right_long(IR3);
IRSensor ir_back_short(IR6);
IRSensor ir_back_long(IR5);
IRSensor ir_left_short(IR8);
IRSensor ir_left_long(IR7);

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
  switch (pin)
  {
    case IR1:
      return min(10, max(0, 0.000000000952 * r * r * r * r
                         - 0.000001737 * r * r * r
                         + 0.001169 * r * r
                         - 0.356 * r
                         + 47.227));
    case IR2:
      return min(10, max(0, 0.000000000952 * r * r * r * r
                         - 0.000001737 * r * r * r
                         + 0.001169 * r * r
                         - 0.356 * r
                         + 47.227));
    case IR3:
      return min(40, max(0, 0.000000001489 * r * r * r * r
                         - 0.000002703 * r * r * r
                         + 0.001808 * r * r
                         - 0.567 * r
                         + 84.406));
    case IR4:
      return min(10, max(0, 0.000000000952 * r * r * r * r
                         - 0.000001737 * r * r * r
                         + 0.001169 * r * r
                         - 0.356 * r
                         + 47.227));
    case IR5:
      return min(40, max(0, 0.0000000008933 * r * r * r * r
                         - 0.000001826 * r * r * r
                         + 0.001359 * r * r
                         - 0.475 * r
                         + 78.776));
    case IR6:
      return min(10, max(0, 0.000000000952 * r * r * r * r
                         - 0.000001737 * r * r * r
                         + 0.001169 * r * r
                         - 0.356 * r
                         + 47.227));
    case IR7:
      return min(40, max(0, -0.0000000004113 * r * r * r * r
                         - 0.000000003918 * r * r * r
                         + 0.0004522 * r * r
                         - 0.286 * r
                         + 64.35));
    case IR8:
      return min(10, max(0, 0.000000000952 * r * r * r * r
                         - 0.000001737 * r * r * r
                         + 0.001169 * r * r
                         - 0.356 * r
                         + 47.227));
  }
}

void IRSensor::serialPrint()
{
  Serial.print(getInches());
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
  Serial.print("\n");
}

