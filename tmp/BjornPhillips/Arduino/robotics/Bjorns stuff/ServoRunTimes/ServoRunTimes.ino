
#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left servo signal
Servo servoRight;                            // Declare right servo signal

void setup()                                 // Built in initialization block
{
  servoLeft.attach(13);                      // Attach left signal to pin 13
  servoRight.attach(12);                     // Attach right signal to pin 12

  servoLeft.writeMicroseconds(1300);         // Pin 13 clockwise
  servoRight.writeMicroseconds(1300);        // Pin 12 clockwise
  delay(3000);                               // ..for 3 seconds
  servoLeft.writeMicroseconds(1700);         // Pin 13 counterclockwise
  servoRight.writeMicroseconds(1700);        // Pin 12 counterclockwise
  delay(3000);                               // ..for 3 seconds
  servoLeft.writeMicroseconds(1500);         // Pin 13 stay still
  servoRight.writeMicroseconds(1500);        // Pin 12 stay still
}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}

