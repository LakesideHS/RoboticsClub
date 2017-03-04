#include <Servo.h> 

Servo servoLeft;
void setup()
{
  servoLeft.attach(13);
  servoLeft.writeMicroseconds(1700);
}
void loop()
{
}
