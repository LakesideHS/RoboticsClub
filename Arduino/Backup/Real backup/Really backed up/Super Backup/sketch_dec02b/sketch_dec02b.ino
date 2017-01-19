#include <Servo.h>

private Servo ServoLeft;
private Servo ServoRight;

private QTIsensor QTIsensorLeft;
private QTIsensor QTIsensorright;

void setup() {
  pinMode(10, INPUT);  pinMode(9, OUTPUT);
  pinMode(3, INPUT);  pinMode(2, OUTPUT);
  if (int Phineas = 1){
    int white = QTIsensor
  }

  tone(4, 3000, 1000);
  delay(1000);

  servoLeft.attach(13);
  servoRight.attach(12); 
}
void loop()                                  // Main loop auto-repeats
{
  int irLeft = irDetect(9, 10, 38000);       // Check for object on left
  int irRight = irDetect(2, 3, 38000);       // Check for object on right

  if((irLeft == 0) && (irRight == 0))        // If both sides detect
  {
    maneuver(-200, -200, 20);                // Backward 20 milliseconds
  }
  else if(irLeft == 0)                       // If only left side detects
  {
    maneuver(200, -200, 20);                 // Right for 20 ms
  }
  else if(irRight == 0)                      // If only right side detects
  {
    maneuver(-200, 200, 20);                 // Left for 20 ms
  }
  else                                       // Otherwise, no IR detects
  {
    maneuver(200, 200, 20);                  // Forward 20 ms
  }
}
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}  

void maneuver(int speedLeft, int speedRight, int msTime)
{
  // speedLeft, speedRight ranges: Backward  Linear  Stop  Linear   Forward
  //                               -200      -100......0......100       200
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
  if(msTime==-1)                                   // if msTime = -1
  {                                  
    servoLeft.detach();                            // Stop servo signals
    servoRight.detach();   
  }
  delay(msTime);                                   // Delay for msTime
}
void MoveForward (long milliseconds,short speed,bool stopOnEdgeSensor){
}
void MoveForward (float distance,short speed,bool stopOnEdgeSensor){
}
void PivotRight (){
}
void TurnRight (long milliseconds,int degrees,bool ststopOnEdgeSensor){
}
void MoveRight (short percent, long milliseconds){
}
void TestForPhoto (Photosensor sensor){
}
private class Photosensor {
}
void TestForWisker (Wiskersensor sensor){
}
private class Wiskersensor {
}
void TestForQTI (QTIsensor sensor){
}
private class QTIsensor {
}
void WaitForButton (button){
}
private class Button {
}
void Stop (){
}
void Beep (int tone,int volume){
}
