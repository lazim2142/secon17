#include <NewPing.h>

#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int distanceInCm;

// motor pin assignment
const int FL_step=9;
const int FR_step=8;
const int BL_step=10;
const int BR_step=11;
const int FL_dir=51;
const int FR_dir=53;
const int BL_dir=49;
const int BR_dir=47;

// pin mode assignment for motor step and direction pins
void setup(){
 pinMode(FL_step,OUTPUT); 
 pinMode(FR_step,OUTPUT);
 pinMode(BL_step,OUTPUT);
 pinMode(BR_step,OUTPUT);
 pinMode(FL_dir,OUTPUT); 
 pinMode(FR_dir,OUTPUT);
 pinMode(BL_dir,OUTPUT);
 pinMode(BR_dir,OUTPUT);
}

void loop(){

  forward ();

  unsigned int uS = sonar.ping();
  distanceInCm = (uS / US_ROUNDTRIP_CM);
    
  while (distanceInCm < 15) {
    stopMotor ();    
    exit(0);
  }
    
}
