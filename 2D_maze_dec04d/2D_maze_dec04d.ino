#include <Servo.h>
Servo servoLeft;
Servo servoRight;

byte wLeftOld;
byte wRightOld;
byte counter;


void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(5, INPUT);  
  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT);

  servoLeft.attach(13);
  servoRight.attach(12);
 
  wLeftOld = 0;
  wRightOld = 1;
  counter = 0;
}

void loop() {

  Maze()
  Exit 0

}

void Maze(){

  MoveForwardUntilWhisker();
  MoveForward(-1);
  TurnRight(135);
  MoveForwardUntilWhisker();
  MoveForward(-1);
  TurnRight(-90);
  MoveForwardUntilWhisker();
  MoveForward(-1);
  TurnRight(-45);
  MoveForwardUntilWhisker();
  MoveForward(-1);
  TurnRight(-90);
  MoveForwardUntilWhisker();
  MoveForward(-1);
  TurnRight(90);
  MoveForwardUntilWhisker();
  

}


long RCTime(int sensorIn) {
  long duration = 0;
  pinMode(sensorIn, OUTPUT);     // Make pin OUTPUT
  digitalWrite(sensorIn, HIGH);  // Pin HIGH (discharge capacitor)
  delay(1);                      // Wait 1ms
  pinMode(sensorIn, INPUT);      // Make pin INPUT
  digitalWrite(sensorIn, LOW);   // Turn off internal pullups
  while (digitalRead(sensorIn)) { // Wait for pin to go LOW
    duration++;
  }
  return duration;
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
  if (msTime == -1)                                // if msTime = -1
  {
    servoLeft.detach();                            // Stop servo signals
    servoRight.detach();
  }
  delay(msTime);                                   // Delay for msTime
}
void MoveForward (long milliseconds, short speed, bool stopOnEdgeSensor) {
}
void MoveForward (float distance, short speed, bool stopOnEdgeSensor) {
}
void PivotRight () {
}
void TurnRight (long milliseconds, int degrees, bool ststopOnEdgeSensor) {
}
void MoveRight (short percent, long milliseconds) {
}
void TestForPhoto (int sensor) {
}
void TestForWisker (int sensor) {
}
void TestForQTI (int sensor) {
}
void WaitForButton (int port) {
}
void Stop () {
}
void Beep (int tone, int volume) {
}
