// ENB 110
// Black 3 or above 
// White 0.25 - 0.32

// Circuits Lab
//black 4.5 - 4.8
//close to white 3.5
//white 0.1 - 0.7

#include "Arduino.h"

// White Thresholds
const float whlimit =  0.35;
const float wllimit = 0;

//Black Thresholds
const float bhlimit = 5;
const float bllimit = whlimit;

// Sensor Layout // Looking from Top Down
//  F1 F2 F3 F4        F5

// Sensor layout // Looking from Top Down
//  L1 L2 L3 L4        L5

const int f1sensor = 4;
const int f2sensor = 3;
const int f3sensor = 2;
const int f4sensor = 1;
const int f5sensor = 0;

const int l1sensor = 12;
const int l2sensor = 11;
const int l3sensor = 10;
const int l4sensor = 9;
const int l5sensor = 8;

// sensor variables // 1 0r 0 depending upon color of the ground
int sensorf1;
int sensorf2;
int sensorf3;
int sensorf4;
int sensorf5;

int sensorl1;
int sensorl2;
int sensorl3;
int sensorl4;
int sensorl5;


float voltagef1;
float voltagef2;
float voltagef3;
float voltagef4;
float voltagef5;

float voltagel1;
float voltagel2;
float voltagel3;
float voltagel4;
float voltagel5;

void getsensors(){

voltagef1 = (analogRead(f1sensor) / 204.6 );
voltagef2 = (analogRead(f2sensor) / 204.6 );
voltagef3 = (analogRead(f3sensor) / 204.6 );
voltagef4 = (analogRead(f4sensor) / 204.6 ); 
voltagef5 = (analogRead(f5sensor) / 204.6 );
  
voltagel1 = (analogRead(l1sensor) / 204.6 );
voltagel2 = (analogRead(l2sensor) / 204.6 );
voltagel3 = (analogRead(l3sensor) / 204.6 );
voltagel4 = (analogRead(l4sensor) / 204.6 );
voltagel5 = (analogRead(l5sensor) / 204.6 );


// Determine which color each sensor is reading

// Front sensors
if (voltagef1 <= whlimit )    // White limits
   sensorf1 = 1; 
if (voltagef1 >= bllimit)    // Black limits
   sensorf1 = 0;
   
if (voltagef2 <= whlimit )    // White limits
   sensorf2 = 1; 
if (voltagef2 >= bllimit)    // Black limits
   sensorf2 = 0;
   
if (voltagef3 <= whlimit )    // White limits
   sensorf3 = 1; 
if (voltagef3 >= bllimit)    // Black limits
   sensorf3 = 0;
   
if (voltagef4 <= whlimit )    // White limits
   sensorf4 = 1; 
if (voltagef4 >= bllimit)    // Black limits
   sensorf4 = 0;
   
if (voltagef5 <= whlimit )    // White limits
   sensorf5 = 1; 
if (voltagef5 >= bllimit)    // Black limits
   sensorf5 = 0;
   

// Left sensors
if (voltagel1 <= whlimit )    // White limits
   sensorl1 = 1; 
if (voltagel1 >= bllimit)    // Black limits
   sensorl1 = 0;
  
if (voltagel2 <= whlimit )    // White limits
   sensorl2 = 1; 
if (voltagel2 >= bllimit)    // Black limits
   sensorl2 = 0;
   
if (voltagel3 <= whlimit )    // White limits
   sensorl3 = 1; 
if (voltagel3 >= bllimit)    // Black limits
   sensorl3 = 0;
   
if (voltagel4 <= whlimit )    // White limits
   sensorl4 = 1; 
if (voltagel4 >= bllimit)    // Black limits
   sensorl4 = 0;
   
if (voltagel5 <= whlimit )    // White limits
   sensorl5 = 1; 
if (voltagel5 >= bllimit)    // Black limits
   sensorl5 = 0;

}  



void testsensors(){

voltagef1 = (analogRead(f1sensor) / 204.6 );
voltagef2 = (analogRead(f2sensor) / 204.6 );
voltagef3 = (analogRead(f3sensor) / 204.6 );
voltagef4 = (analogRead(f4sensor) / 204.6 ); 
voltagef5 = (analogRead(f5sensor) / 204.6 );
  
voltagel1 = (analogRead(l1sensor) / 204.6 );
voltagel2 = (analogRead(l2sensor) / 204.6 );
voltagel3 = (analogRead(l3sensor) / 204.6 );
voltagel4 = (analogRead(l4sensor) / 204.6 );
voltagel5 = (analogRead(l5sensor) / 204.6 );


Serial.print("F1 Voltage = "); Serial.println(voltagef1);
Serial.print("F2 Voltage = "); Serial.println(voltagef2);
Serial.print("F3 Voltage = "); Serial.println(voltagef3);
Serial.print("F4 Voltage = "); Serial.println(voltagef4);
Serial.print("F5 Voltage = "); Serial.println(voltagef5); Serial.println();

Serial.print("L1 Voltage = "); Serial.println(voltagel1);
Serial.print("L2 Voltage = "); Serial.println(voltagel2);
Serial.print("L3 Voltage = "); Serial.println(voltagel3);
Serial.print("L4 Voltage = "); Serial.println(voltagel4);
Serial.print("L5 Voltage = "); Serial.println(voltagel5); Serial.println();

// Determine which color each sensor is reading

// Front sensors
if (voltagef1 <= whlimit )    // White limits
   sensorf1 = 1; 
if (voltagef1 >= bllimit)    // Black limits
   sensorf1 = 0;
   
if (voltagef2 <= whlimit )    // White limits
   sensorf2 = 1; 
if (voltagef2 >= bllimit)    // Black limits
   sensorf2 = 0;
   
if (voltagef3 <= whlimit )    // White limits
   sensorf3 = 1; 
if (voltagef3 >= bllimit)    // Black limits
   sensorf3 = 0;
   
if (voltagef4 <= whlimit )    // White limits
   sensorf4 = 1; 
if (voltagef4 >= bllimit)    // Black limits
   sensorf4 = 0;
   
if (voltagef5 <= whlimit )    // White limits
   sensorf5 = 1; 
if (voltagef5 >= bllimit)    // Black limits
   sensorf5 = 0;
   

// Left sensors
if (voltagel1 <= whlimit )    // White limits
   sensorl1 = 1; 
if (voltagel1 >= bllimit)    // Black limits
   sensorl1 = 0;
  
if (voltagel2 <= whlimit )    // White limits
   sensorl2 = 1; 
if (voltagel2 >= bllimit)    // Black limits
   sensorl2 = 0;
   
if (voltagel3 <= whlimit )    // White limits
   sensorl3 = 1; 
if (voltagel3 >= bllimit)    // Black limits
   sensorl3 = 0;
   
if (voltagel4 <= whlimit )    // White limits
   sensorl4 = 1; 
if (voltagel4 >= bllimit)    // Black limits
   sensorl4 = 0;
   
if (voltagel5 <= whlimit )    // White limits
   sensorl5 = 1; 
if (voltagel5 >= bllimit)    // Black limits
   sensorl5 = 0;


Serial.println();
Serial.print("F1 Sensor = "); Serial.println(sensorf1);
Serial.print("F2 Sensor = "); Serial.println(sensorf2);
Serial.print("F3 Sensor = "); Serial.println(sensorf3);
Serial.print("F4 Sensor = "); Serial.println(sensorf4);
Serial.print("F5 Sensor = "); Serial.println(sensorf5); Serial.println();

Serial.print("L1 Sensor = "); Serial.println(sensorl1);
Serial.print("L2 Sensor = "); Serial.println(sensorl2);
Serial.print("L3 Sensor = "); Serial.println(sensorl3);
Serial.print("L4 Sensor = "); Serial.println(sensorl4);
Serial.print("L5 Sensor = "); Serial.println(sensorl5); Serial.println();

Serial.println();

}  
