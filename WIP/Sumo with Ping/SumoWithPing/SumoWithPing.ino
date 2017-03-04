#include <Servo.h>
#include <SonarI2C.h>

/*  Lakeside High School Robotics Club
	ObjectTrackingWithPing
	
  We are using the SonarI2C header to provide services for the Ping Sensor.

  	This Arduino sketch uses two of the HC-SR04 Sensor 
  	(4-pin Ping Sensor) to track an object moving near it.
  	
  	The HC-SR04 has the foloing pin-out configuration:
  	* VCC (+5V power)
  	* TRIG (Digital Input)
  	* ECHO (Digital Output)
  	* GND (ground)
  		
  We are using the Servo header to provide services for the Continuous Rotation Servos.

    We are passing values from 0 to 180 to the servos.  those values are mapping to
    0   = Full anti-clockwize
    90  = Full stop
    180 = Full clockwize
*/

//Create the objects
SonarI2C leftSonar(0x20, 4, 4000);
SonarI2C rightSonar(0x20, 5, 4000);
Servo leftServo;
Servo rightServo;
int trackingSpeed = 0;
int trackingIncriment;
int maxTrackingSpeed;
int maxTargetDistance;
int currSpeed;
uint32_t last_time = 0;


void Track() {
    //read the number of inches to target from each ping
    int leftRead = leftSonar.inch();
    int rightRead = rightSonar.inch();

    //adjust tracking speed as needed
    if (leftRead>maxTargetDistance && rightRead>maxTargetDistance) {
      //We need to aquire the target
      trackingSpeed = maxTrackingSpeed; 
    } else if (leftRead>rightRead) {
      //track faster right
      trackingSpeed = max (trackingSpeed + trackingIncriment,maxTrackingSpeed);
    } else if (leftRead<rightRead) {
      //track faster left
      trackingSpeed = min (trackingSpeed - trackingIncriment, -maxTrackingSpeed);
    } else {
      //no change
    trackingSpeed = 0;
    }  
    //Serial.print("SONAR: ");  
    Serial.println(leftRead);          
    //Serial.print("          "); 
    //Serial.println(rightRead);
}
 
void setup() {
  Serial.begin(115200);

  //Sonar setup
  SonarI2C::begin();   			// initialize bus, pins etc
  SonarI2C::inverse = false;  	// NOR logic
  leftSonar.init();   			// clear expander and add to list
  rightSonar.init();    			// clear expander and add to list

  //Servo setup
  leftServo.attach(12,1300,1700);
  rightServo.attach(13,1300,1700);

  SetupTracking();
  //SetupSumo();
}



void loop() {
  LoopTracking();
  //LoopSumo();
}


void SetupTracking() {
  //Set up variables needed for Sumo
  trackingIncriment = 10;
  maxTrackingSpeed = 90;
  maxTargetDistance = 30;
  currSpeed = 0;
}

void SetupSumo() {
  //Set up variables needed for Sumo
  trackingIncriment = 10;
  maxTrackingSpeed = 90;
  maxTargetDistance = 30;
  currSpeed = 30;


  //Get into attack position (A couple inches inside the border facing right)

}


void LoopTracking() {
  SonarI2C::doSonar();  // call every cycle, SonarI2C handles the spacing

  if (last_time + 100 < millis()) {
    last_time=millis();

    Track();

    leftServo.write(90+trackingSpeed);
    rightServo.write(90-trackingSpeed);

    //Serial.print("SERVO: ");  Serial.print(leftServo.read());  Serial.print"          ");  Serial.println(rightServo.read();
  }
}

void LoopSumo() {
  SonarI2C::doSonar();  // call every cycle, SonarI2C handles the spacing

  if (last_time + 100 < millis()) {
    last_time=millis();

    Track();

    leftServo.write(-currSpeed+trackingSpeed);
    rightServo.write(currSpeed+trackingSpeed);

    //Serial.print("SERVO: ");  Serial.print(leftServo.read());  Serial.print"          ");  Serial.println(rightServo.read();
  }
}


