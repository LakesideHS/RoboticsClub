/* 
  Step 2: Now lets get the sensors working together.  We need to set up #define statements for each sensor.

    1. Update the define statements to have a TRIGGER_PIN and ECHO_PIN defined for each sensor
    2. Duplicate the NewPing declaration statement ("NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);").
    3. Update the NewPing declarations to use the sensor-specific constants. 
    4. Change the Serial Print statemetns to output both sensor values
    5. Uplade the sketch to the robot.
    4. Start the Serial Monitor and set it to 115200 baud.
    5. You should see "." printed unless there is an object within 25 inches.
*/

#include <NewPing.h>

//Set up the constants.  we use #Define instead of variables because it uses less space and is faster
#define TRIGGER_PIN_LEFT  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.                   //   <-Change: Add "_LEFT"
#define ECHO_PIN_LEFT     6  // Arduino pin tied to echo pin on the ultrasonic sensor.                      //   <-Change: Add "_LEFT"
#define TRIGGER_PIN_RIGHT 3  // Arduino pin tied to trigger pin on the ultrasonic sensor.                   //   <-Change: Copy and Paste then change "_LEFT" to "_RIGHT"
#define ECHO_PIN_RIGHT    4  // Arduino pin tied to echo pin on the ultrasonic sensor.                      //   <-Change: Copy and Paste then change "_LEFT" to "_RIGHT"
#define MAX_DISTANCE 64 // Maximum distance we want to ping for (in centimeters). 25 inches = 63.5 cm.

NewPing leftSonar(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE);                                           //   <-Change: Renamed to leftSonar and use _LEFT constants
NewPing rightSonar(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);                                        //   <-Change: Copy and change "_LEFT" to "_RIGHT"

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  Serial.println("Ping: LEFT: " + String(leftSonar.ping_mm()) + 
    "cm       RIGHT: " + String(leftSonar.ping_mm()) + "cm");

}
