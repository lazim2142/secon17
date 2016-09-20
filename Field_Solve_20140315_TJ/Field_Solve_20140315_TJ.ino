#include <Servo.h>
#include <TimerOne.h>

// Solve the Field // Borrowed from 0312 with sweep that works well
                   // Add color start
                   // Changed anlges on arm 41 and 137, 122 Fire at target
                   // Add stop on endzone
                   // Add 8th stepping changes/
                   // Add Start block changes

// White for both sensor strips is about 0.2
// Black for both sensor strips is about 3 or higher

// This program can solve the field all the way through
// This needs calibrate program, and camera program added


#include "sensors.h";
#include "motors.h";
#include "nerfgunfire.h";
#include "calibrate.h"
#include "armMove.h";
#include "color.h";

int stepcount;

void setup (){

  motorsetup();
  //armSetup();
  Serial.begin(9600);  
  pinMode(5, INPUT); // Start Button
  pinMode(gunpin, OUTPUT); //Gun Pin
  
  // Enable motors to keep from moving around
  digitalWrite(M1EPin, 0);
  digitalWrite(M2EPin, 0);
  digitalWrite(M3EPin, 0);
  digitalWrite(M4EPin, 0);
  
  // Initialize the arm
  arminit();
}

void loop(){

  // Wait for Start button to be pushed  
  // Sean - Set as input, then write high to the line, tie the switch to grnd.
  
  float start = 2;
  digitalWrite(5, HIGH);
  disablemotors();
  
  while (start != LOW){
    start = digitalRead(5);
    //Serial.print("Start Voltage = "); Serial.println(start);
  }
  enablemotors();
  
  //delay(10000);
  
  //waitForGo(); //waits for green light signal

  delay(2000); fieldsolve();
  
  //delay(2000);  testsensors();

  //delay(2000); testsensordist();
  
  //delay(4000); calibrate(); delay(6000);
  
  //arminit();
  //disablemotors();
  //delay(1000); armmoveblock2();
  
  // delay(2000); testarmsensordist();

  //delay(200000);

}



void block1(){
  
  int stepcount = 0;
  int i= 0;
  
  getsensors();
  
  // Move away from the starting block a few steps // Full 50, Half - 100, Quarter - 200, 8th - 400
  for (int i=0; i< 1200; i++){
    north();
    stepcount ++;
  }
  
 while (sensorf2 == 0 || sensorf3 == 0 || sensorf1 == 0){
    ne();
    getsensors();
    stepcount++;
  }
  
  // Go straight down the line until it finds the turning point
  while (true){
    getsensors();

    movenorth();

    // Finds the turning point to the blue block1 // 300 steps for full, 600 half, 1200 quarter, 2400 - 8th
    if (sensorl2 == 1 && stepcount > 2400){
      
       // Dead Stop
       delay(250);
       
       
       // Sensor is on right side, go forward a few steps
       for (i=0; i<850; i++){
        movewest(); 
       }
      
        stepcount = 0;
    
       // Go straight until Blue block has been found, then stop          
       while (true){
          stepcount++;
      
          // Blue block1 has been found - Move on top of block and stop - Break from Block1 function
          if ((analogRead(l1sensor)/204.5) < .5 && voltagel2 < .5 && voltagel3 < .5 && stepcount > 850){    // Old - Preset steps only // if (stepcount == 200)
            // Move forward XXXX steps, then stop on top of the blue block // 75 Full, 150 Half, 300 quarter, 600 - 8th
            //for (i=0; i<600; i++){
            //  east();                
            //}
            
            // Wait unitl robot settles from movement
            delay(1500);    

            halfdisablemotors();
            armmoveblock1();
            //delay(100);
            arminit();
            enablemotors();
            
            return;
          }      
      
          // Otherwise continue to go west until the block1 has been found     
          movewest();    
       } 
    }    
  stepcount++;  
  }
}


// Movement from block1 to block2
void block2(){
  
  int stepcount = 0; 
  int i= 0;
  
  getsensors();
  
  // Go straight down the line 
  while (true){
       getsensors();
    
       moveeast();
 
    // Finds the turning point for the main line to go North
    if (sensorf3 == 1 && sensorf2 == 1){

         // Dead stop to allow robot movement to settle
         delay(250);       
         
         // reset the step count
         stepcount = 0;
         
         // Go straight down the main line (North) until turning point for next line is found      
         while (sensorf2 == 1 || sensorf3 == 1){
         
            getsensors();
    
            movenorth();
            
            stepcount++;
            
            // Finds the turning point for block2 line // 20 Full, 40 Half, 80 Quarter, 160 - 8th
            if (sensorl2 == 1 && stepcount > 160){

               // Dead stop
               delay(250);
               stepcount = 0;
               
               // Sensor is on right side, go forward a few steps
               for (i=0; i<850; i++){
                 movewest(); 
               }
               
               // Head down to find block2
               while (true){
      
                  stepcount++;
      
                  // Blue block2 has been found - Move on top of block and stop - Break from Block1 function
                  if ((analogRead(l1sensor)/204.5) < .7 && voltagel2 < .7 && voltagel3 < .7 && stepcount > 850){ 
                    //for (i=0; i<600; i++){              // 75 Full, 150 Half, 300 Quarter, 600 - 8th
                    //  east();                
                    //}
                    
                    // Delay to allow robot movement to settle
                    delay(1500);    

                    halfdisablemotors();
                    armmoveblock2();
                    //delay(100);
                    arminit();
                    enablemotors();

                    delay(100);

                    return;
                  }      
      
                  // Otherwise continue to go straight until the block2 has been found     
                  movewestblock2();
               
                 } // End While
            } // End If
         } // End While 
    } // End If
  } // End While 
} // End Block2




// Movement from block2 to block3
void block3(){
  
  int stepcount = 0; 
  int i= 0;
  
  getsensors();
  
  // Go straight down block2 line 
  while (true){
       getsensors();
    
       moveeastblock2();
 
    // Finds the turning point for the main line to go North
    if (sensorf2 == 1 && sensorf3 == 1){

         // Dead stop to allow robot movement to settle
         delay(250);
         
         // Speed up
         //speedupwest(); 
         
         // reset the step count
         stepcount = 0;
         
         // Go straight down the main line (North) until turning point for next line is found      
         while (true){
         
            getsensors();
    
            movenorth();
            
            stepcount++;
            
            // Finds the turning point for block3 line // 20 Full, 40 Half, 80 Quarter, 160 - 8th
            if (sensorl2 == 1 && stepcount > 160){

               // Dead stop
               delay(250);
               stepcount = 0;
               
               // Head down to find block3
               while (true){
      
                  stepcount++;
      
                  // Blue block3 has been found - Move on top of block and stop - Break from Block1 function
                  if ((analogRead(l1sensor)/204.5) < .7 && voltagel2 < .7 && voltagel3 < .7 && stepcount > 850){ 
                    //for (i=0; i<600; i++){              // 75 Full, 150 Half, 300 Quarter, 600 - 8th
                    //  east();                
                    //}
                    
                    // Delay to allow robot movement to settle
                    delay(1500);    

                    halfdisablemotors();
                    armmoveblock3();
                    //delay(100);
                    arminit();
                    enablemotors();

                    delay(100);

                    return;
                  }      
      
                  // Otherwise continue to go straight until the block3 has been found     
                  movewest();
               
                 } // End While
            } // End If
         } // End While 
    } // End If
  } // End While 
} // End Block3




void endzone(){
  
 // Movement from block3 to endzone
 
  int stepcount = 0; 
  int i= 0;
  
  getsensors();
  
  // Go straight down the line 
  while (sensorl3 == 1 || sensorl2 == 1){
       getsensors();
    
    moveeast();
 
    // Finds the turning point
    if (sensorf3 == 1 && sensorf2 == 1){

         // Dead stop
         delay(250);
     
         // Go straight until endzone is found     
         while (sensorf2 == 1 || sensorf3 == 1){
         
            getsensors();
    
            movenorth();
  
            // Finds the Black area at the end of the endzone
            if (voltagef2 > 1 && voltagef3 > 1){
               
               // Move forward XXXX steps, then stop on top of the red block
               while (true){    // 50 Full, 100 Half, 200 Quarter, 400 - 8th
                 north();
                 
                 if (voltagef2 > 4){
                    // Dead stop
                    delay(30000);
                    stepcount = 0;
                 }
               }
               
               // Dead stop
               delay(30000);
               stepcount = 0;
               
            }
            
         } // End While 
    } // End If
  } // End While 
} // End Endzone



void fieldsolve(){
  //delay(4000);  
  block1(); // Works good so far // still needs more sensors, and a calibration feature to follow the line better

  delay(1000);  
  block2(); // Works much better, still needs to follow block2/curved line better

  delay(1000);  
  block3();

  delay(1000);  
  endzone();  
}




