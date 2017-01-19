#include <Servo.h>

Servo servoLeft;
Servo servoRight;

void setup() {
  
  servoLeft.attach(13);
  servoRight.attach(12);
  
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(10000);
  
  servoLeft.detach();
  servoRight.detach();
}

void loop() {
}
