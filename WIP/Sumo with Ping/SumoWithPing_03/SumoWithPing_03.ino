
/* 
  Step 2: Add basic tracking of objects within range.

    1. Add the Servo library to the sketch
	2. Add the define statements for the Servos.
	3. declare the servos.
	3. Call the Attach method to tie the servos to the ports
    5. Uplade the sketch to the robot.
    4. Start the Serial Monitor and set it to 115200 baud.
    5. You should see "." printed unless there is an object within 25 inches.
*/

#include <Servo.h>
#include <NewPing.h>


//Set up the constants.  we use #Define instead of variables because it uses less space and is faster
// Sonar Constants
#define TRIGGER_PIN_LEFT  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.                  
#define ECHO_PIN_LEFT     6  // Arduino pin tied to echo pin on the ultrasonic sensor.                     
#define TRIGGER_PIN_RIGHT 3  // Arduino pin tied to trigger pin on the ultrasonic sensor.                  
#define ECHO_PIN_RIGHT    4  // Arduino pin tied to echo pin on the ultrasonic sensor.                     
#define MAX_DISTANCE 64      // Maximum distance we want to ping for (in centimeters). 25 inches = 63.5 cm.
// Servo Constants
#define SERVO_PIN_LEFT    12
#define SERVO_PIN_RIGHT   13
#define TRACKING_SPEED    10
#define TRACKING_INCREMENT 50


//Declare Sensors
NewPing leftSonar(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE);                                          
NewPing rightSonar(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);                                       

//Declare Actuators
Servo leftServo;
Servo rightServo;
int leftServoSpeed = 0;
int rightServoSpeed = 0;




void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  
  //Attach the servos
  leftServo.attach(SERVO_PIN_LEFT,1300,1700);   //Declare Servo with Min and Max values
  rightServo.attach(SERVO_PIN_RIGHT,1300,1700); //Declare Servo with Min and Max values
}





void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  //Call the tracking routine to set find or chase
  Track();
    
  //Serial.println("Ping: LEFT: " + String(leftSounding) + 
  //  "cm       RIGHT: " + String(rightSounding) + "cm");
}

void Track() {
  //read in the values from the sonar sensors:
  int leftSounding = leftSonar.ping_cm();
  int rightSounding = rightSonar.ping_cm();

  //Set NO READ to 1000 for easy math
  if (leftSounding == 0) {leftSounding=1000;}
  if (rightSounding == 0) {rightSounding=1000;}
  
  if (leftSounding+rightSounding == 2000) {
    //We don't see anything. 
  } else if (leftSounding<rightSounding) {
	//The object is to the left
    TrackLeft();
  } else if (rightSounding<leftSounding) {
	//The object is to the right
    TrackRight();
  } else {
	//The object is directly in front 
    TrackForward();
  }
}


void TrackLeft(){
  SetServoSpeed(leftServo,leftServoSpeed+TRACKING_SPEED);
  SetServoSpeed(rightServo,rightServoSpeed+TRACKING_SPEED);
  delay(TRACKING_INCREMENT);
  TrackForward();
}

void TrackRight() {
  SetServoSpeed(leftServo,leftServoSpeed-TRACKING_SPEED);
  SetServoSpeed(rightServo,rightServoSpeed-TRACKING_SPEED);
  delay(TRACKING_INCREMENT);
  TrackForward();
}

void TrackForward() {
  SetServoSpeed(leftServo,leftServoSpeed);
  SetServoSpeed(rightServo,rightServoSpeed);

}

//SetServoSpeed (Servo servo, int speed)
// Sets a servo to the desired speed where speed is a percentage of full
// Allowable range is -100 to 100
void SetServoSpeed(Servo servo, int speed){
  servo.write(map(speed,-100,100,0,180));
}

//GetServoSpeed (Servo servo)
//  Returns the current speed of the servo as a percentage of full
//  Expected return value range is -100 to 100
int GetServoSpeed(Servo servo){
  return map(servo.read(),0,180,-100,100);
}

