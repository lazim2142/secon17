#include "Arduino.h"


int left;
int right;
int up;
int down;

Servo servoTop;
Servo servoBottom;


void armSetup() {
  servoTop.attach(7);
  servoBottom.attach(6);
  //left = 70;
  //right = 50;
  //up = 50;
  //down = 70;
}

void armLeft() {
  servoBottom.write(left);
}

void armRight() {
  servoBottom.write(right);
}

void armUp(){
  servoTop.write(up);
}

void armDown(){
  servoTop.write(down);
}

void disableArm(){
servoTop.detach();
servoBottom.detach();
}

void enableArm(){
  servoTop.attach(7);
  servoBottom.attach(6);
  
}

void arminit(){

  servoBottom.attach(6);         // Attach bottom servo to pin 6
  servoBottom.write(41);        // Starting angle to move the bottom servo
  servoBottom.detach();         // Detach bottom servo to pin 6
  
  servoTop.attach(7);            // Attach top servo to pin 11  
  servoTop.write(137);            // Starting angle to move the top servo // Used to read 95 for some reason
  servoTop.detach();            // Detach top servo to pin 11

  
}

float armsensordist(){
  
  int sensorir = 15;
  float sensorValue, inchdist, cmdist;
  
  sensorValue = analogRead(sensorir);
  sensorValue = analogRead(sensorir);
  inchdist = 4192.936 * pow(sensorValue,-0.935) - 3.937;
  cmdist = 10650.08 * pow(sensorValue,-0.935) - 10;
  delay(50);
  //Serial.print("CM: ");
  //Serial.println(cmdist); //Serial.println();
  //Serial.print("SensorValue: ");
  //Serial.println(sensorValue); Serial.println();
  
  return inchdist;  
}

void testarmsensordist(){
  
  float dist = armsensordist();
  
  Serial.print("dist: ");
  Serial.println(dist); Serial.println();
  
  //delay (2000);
  
}

void armmoveblock1(){
  
    // Attach Servo Arms
    servoTop.attach(7);
    servoBottom.attach(6);
  
    double postdistmax = 35;  // If the sensor sees a distance below this point, it is the post
    double i=0;

    double ipangle = 0;                // Initial Post angle starts at 0 degrees 
    double epangle;                    // End Post angle
    double mpangle;                    // Middle Post angle
    
    // Height distance between gun and target
    const double gunheight = 16;            // in in
    const double targetheight = 27;         // in in
    
    const double adjustment = 0;           // Adjustment for servo motor angle
    
    // Scan incrementally for the post
    for (i = 10; i < 75; i = i+ 0.25){ // vs 1
      
     double inchdist = armsensordist();
     
     // Check to make sure it is finding the post
     //delay(30); testarmsensordist();
      
     // Move to angle incrementally 1 degree at a time
     servoBottom.write(i);   
    
      // End of the Post has been reached
      if (inchdist < postdistmax){
        
        double num = 0;
        epangle = i;
       
       
        double postdist = inchdist;
        
        // Scan until the end of post has been reached
        /*
        while (inchdist < postdistmax){
          servoBottom.write(epangle);
          epangle = epangle + 1;
          num++;
          inchdist = armsensordist();
         //Serial.print(inchdist);   
          
          // Test 
          //delay(1000);
          //testarmsensordist();
        } 
        */
      double halfnum = (num/2);  
      mpangle = (epangle - (num/2));
  
      // Scan to middle of post dependent upon what number is returned. Go back half of that.
      servoBottom.write(epangle-.5); //mpangle old 
      
      // Adjust the upper arm angle
      double y = targetheight - gunheight;
      double x = postdist;
      double theta = (95 - atan(y/x));
      //double r = (x / cos(theta));
      
      servoTop.write(120); //120 is working well
      delay(300);
      nerfgunfire();
      delay(50);
   
      // Return arm to initialization spot
      arminit();
   
      return;
      
      } // End of the if Statement
    } // End of the For loop
}

void armmoveblock2(){
  
    // Attach Servo Arms
    servoTop.attach(7);
    servoBottom.attach(6);
    
    double postdistmax = 65;  // If the sensor sees a distance below this point, it is the post
    double i=0;                //MIDDLE of BLOCK 2 max distance 47
                               //RIGHT SIDE of BLOCK 2 max distance is 52
                               //LEFT Side of BLOCK 2 max distance is 48
                               //Try using under 52 overall

    double ipangle = 0;                // Initial Post angle starts at 0 degrees 
    double epangle;                    // End Post angle
    double mpangle;                    // Middle Post angle
    
    // Height distance between gun and target
    const double gunheight = 16;            // in in
    const double targetheight = 27;         // in in
    
    const double adjustment = 0;           // Adjustment for servo motor angle
    
    
    
    // Scan incrementally for the post
    for (i = 0; i < 75; i++){
      
     double inchdist = armsensordist();
     
     // Check to make sure it is finding the post
     //delay(50); testarmsensordist();
     
     
     // Move to angle incrementally 1 degree at a time
     servoBottom.write(i);   
         
      // End of the Post has been reached
      if (inchdist < postdistmax){
        
        double num = 0;
        epangle = i;
       
       
        double postdist = inchdist;
        
        // Scan until the end of post has been reached
        while (inchdist < postdistmax){
          servoBottom.write(epangle);
          epangle = epangle + 0.25;
          num++;
          inchdist = armsensordist();   
          
          // Test 
          //delay(1000);
          //testarmsensordist();
        } 
          
      double halfnum = (num/2);  
      mpangle = (epangle - (num/2));
  
      // Scan to middle of post dependent upon what number is returned. Go back half of that.
      servoBottom.write(mpangle); 

      // Adjust the upper arm angle
      //double y = targetheight - gunheight;
      //double x = postdist;
      //double theta = (95 - atan(y/x));
      //double r = (x / cos(theta));
      
      servoTop.write(118);
      nerfgunfire();

      // Return arm to initialization spot
      arminit();
      
      return;
      
      } // End of the if Statement
    } // End of the For loop
}

void armmoveblock3(){
  
    // Attach Servo Arms
    servoTop.attach(7);
    servoBottom.attach(6);
  
    double postdistmax = 64;  // If the sensor sees a distance below this point, it is the post
    double i=0;                //MIDDLE of BLOCK 2 max distance 
                               //RIGHT SIDE of BLOCK 2 max distance is 68
                               //LEFT Side of BLOCK 2 max distance is 48
                               //Try using under 52 overall

    double ipangle = 0;                // Initial Post angle starts at 0 degrees 
    double epangle;                    // End Post angle
    double mpangle;                    // Middle Post angle
    
    // Height distance between gun and target
    const double gunheight = 16;            // in in
    const double targetheight = 27;         // in in
    
    const double adjustment = 0;           // Adjustment for servo motor angle
    
    
    
    // Scan incrementally for the post
    for (i = 0; i < 75; i++){
      
     double inchdist = armsensordist();
     
     // Check to make sure it is finding the post
     //delay(50); testarmsensordist();
     
          
     // Move to angle incrementally 1 degree at a time
     servoBottom.write(i);   

      // End of the Post has been reached
      if (inchdist < postdistmax){
        
        double num = 0;
        epangle = i;
       
       
        double postdist = inchdist;
        
        // Scan until the end of post has been reached
        while (inchdist < postdistmax){
          servoBottom.write(epangle);
          epangle = epangle + 0.25;
          num++;
          inchdist = armsensordist();   
          
          // Test 
          //delay(1000);
          //testarmsensordist();
        } 
          
      double halfnum = (num/2);  
      mpangle = (epangle - (num/2));
  
      // Scan to middle of post dependent upon what number is returned. Go back half of that.
      servoBottom.write(mpangle); 
       
      // Adjust the upper arm angle
      //double y = targetheight - gunheight;
      //double x = postdist;
      //double theta = (95 - atan(y/x));
      //double r = (x / cos(theta));
      
      servoTop.write(116);
      nerfgunfire();
 
      // Return arm to initialization spot
      arminit();
      
      return;
      
       } // End of the if Statement  
    } // End of the For loop
}
