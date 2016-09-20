

//#include "Arduino.h"

const int TRIGGER_PIN = 53;
const int ECHO_PIN = 49;
const int MAX_DISTANCE = 200;

//#define TRIGGER_PIN  53  // Arduino pin tied to trigger pin on the ultrasonic sensor.
//#define ECHO_PIN     49  // Arduino pin tied to echo pin on the ultrasonic sensor.
//#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

unsigned int pingtime;
float pingdist;

void ping(){
  
      delay(50);                                       // Wait 50ms between pings
      pingtime = sonar.ping();                         // Send Ping, and return ping time in uS
      pingdist = pingtime / US_ROUNDTRIP_CM;           // Convert Ping time to distance in cm  
}
