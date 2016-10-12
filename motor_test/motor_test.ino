#include <Servo.h>
#include "sensors.h";
#include "motors.h";
#include "nerfgunfire.h";
#include "calibrate.h"

#define r_sensor_pin A3

void setup ()
{
  motorsetup();
  disablemotors();

  //pinMode(r_sensor_pin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(getRDist());
  float rs_dist = analogRead(r_sensor_pin);   // meters
}

float getRDist()
{
  float r = analogRead(r_sensor_pin);
  return min(20, max(0, 0.000000000952 * r * r * r * r
                     - 0.000001737 * r * r * r
                     + 0.001169 * r * r
                     - 0.356 * r
                     + 47.227));
}
