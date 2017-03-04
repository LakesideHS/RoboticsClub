/* 
  Step 1: We test One Snesor using the sample code provided in the NewPing library.

    1. Copy and paste the code from NewPing_Example
    2. Update the #define statements:
        Use the correct pins for one sensor.
        Set the max distance to 64 (just over 25 inches)
    3. Upload the code to the robot.
    4. Start the Serial Monitor and set it to 115200 baud.
    5. You should see 0cm unless there is an object within 25 inches.
    6. Switch out the pin numbers in the define statements and test the other ping sensor then do 3,4,5 again.
*/

// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 64 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  String output = 
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}
