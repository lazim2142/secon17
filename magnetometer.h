#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H
#include "SparkFun_MAG3110.h"

namespace Magnetometer
{
MAG3110 mag = MAG3110();

void init()
{
  mag.initialize();
  mag.setDR_OS(MAG3110_DR_OS_80_16);
  mag.start();
}

bool fieldDetected()
{
  float x = 0, y = 0, z = 0;
  if (mag.dataReady())
    mag.readMicroTeslas(&x, &y, &z);
  return sqrt(x * x + y * y + z * z) > 300;
}

}
#endif
