// Calibrate

#include "Arduino.h"

int totalscan = 30;
int startscan = (totalscan/2); // This the scan will start
int backstep;
float distArray[30];
int positionvalue = 0;
int i;

// IR Sensor Query constants
#define sensorIR 5               //Must be an analog pin
//#define 
float sensorValue, inchdist, cmdist;    //Must be of type float for pow()

//MinValue constants
float minValue = distArray[0]; 
int positionValue;


// Step
void Step(){
  
  // High
  digitalWrite(M1SPin, HIGH);
  digitalWrite(M2SPin, HIGH);
  digitalWrite(M3SPin, HIGH);  
  digitalWrite(M4SPin, HIGH);  
  
  delayMicroseconds(500);

  // Low 
  digitalWrite(M1SPin, LOW);
  digitalWrite(M2SPin, LOW);
  digitalWrite(M3SPin, LOW);  
  digitalWrite(M4SPin, LOW);  
  
  delayMicroseconds(500);
  
  //delayMicroseconds(5000);  
}


float sensordist(){
  int sensorir = 5;
  float sensorValue, inchdist, cmdist;
  
  sensorValue = analogRead(sensorir);
  inchdist = 4192.936 * pow(sensorValue,-0.935) - 3.937;
  cmdist = 10650.08 * pow(sensorValue,-0.935) - 10;
  delay(100);
  //Serial.print("CM: ");
  //Serial.println(cmdist); //Serial.println();
  //Serial.print("SensorValue: ");
  //Serial.println(sensorValue); Serial.println();
  
  return inchdist;
}

void testsensordist(){
  
  float dist = sensordist();
  
  Serial.print("dist: ");
  Serial.println(dist); Serial.println();
  
  //delay (2000);
  
}

void findMinValue(){
  minValue = distArray[0];
  
   for (int x = 0; x < totalscan; x++){

      if (distArray[x] < minValue){ //if value at x is lower than minValue

         minValue = distArray[x]; //minValue gets value at x
         positionValue = x;
      }   
   }   
}

void calibrate(){
  
  // Set Directions for C-Clockwise rotation
  digitalWrite(M1DPin, 1);       // C-Clockwise
  digitalWrite(M2DPin, 1);       // C-Clockwise
  digitalWrite(M3DPin, 1);       // C-Clockwise
  digitalWrite(M4DPin, 1);       // C-Clockwise 
  
  // Rotate C-Clockwise startscan steps
  for (i=0; i < startscan; i++){
    //for (i=0; i<2; i++){
    Step();
    //}
  }

  // Set Directions for Clockwise rotation
  digitalWrite(M1DPin, 0);       // Clockwise
  digitalWrite(M2DPin, 0);       // Clockwise
  digitalWrite(M3DPin, 0);       // Clockwise
  digitalWrite(M4DPin, 0);       // Clockwise 

  // Rotate Clockwise totalscan steps
  for (i=0; i < totalscan; i++){
    //for (i=0; i<2; i++){
    Step();
    //}
    distArray[i] = sensordist(); // IR return distance
  }

  // Find the shortest distance to the wall
  findMinValue();
  
  // Rotate C-Clockwise (totalscan - positionValue) steps
  backstep = totalscan - positionValue;
  //int backstep = totalscan - excess;

  // Set Directions to rotate C-Clockwise
  digitalWrite(M1DPin, 1);       // C-Clockwise
  digitalWrite(M2DPin, 1);       // C-Clockwise
  digitalWrite(M3DPin, 1);       // C-Clockwise
  digitalWrite(M4DPin, 1);       // C-Clockwise 

  for (i=0; i < backstep; i++){
   //for (i=0; i<2; i++){
    Step();
   // }
  }
  
  /*
  // Query the Left sensors // Move North or South Depending on Sensor input, until LC and LR values are back on white line
  getsensors();
  
  // First try to moove south to find the line
  if (voltagell > 0.4 && voltagelc > 0.4 && voltagelr > 0.4){
     for (i=0; i<20; i++ ){
      
      getsensors();
      south();
      
      if (voltagelr < 0.4){
        goto exit;
      }
      
       
     }
  }
    
    // If the line hasn't been found going south, then go north to try to find the line
    if (voltagell > 0.4 && voltagelc > 0.4 && voltagelr > 0.4){
     for (i=0; i<40; i++ ){
      
      getsensors();
      north();
      
      if (voltagelr < 0.4){
        goto exit;
      }
      
       
     }
  }
  
  // Hopefully the line has been found by this point
  */
exit: ;
}







