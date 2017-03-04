#include <Servo.h>
Servo servoLeft;
Servo servoRight;
int servoZero = 1500;
int servoMax = 200;
int qtiThreshhold = 500;
//Sensors
byte LeftWhisker = 2;
byte RightWhisker = 1;
byte inches;
int leftFrontPhoto = 9;
int rightFrontPhoto = 10;
int leftBackPhoto = 7;
int rightBackPhoto = 8;

//Timing
int HalfTurnMilliseconds=1350;
/////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(5, INPUT);

  servoLeft.attach(13);
  servoRight.attach(12);
  //maze1();
  TurnRight(-75);
}

void loop(){
  //Stop;
  //Maze;
  loopSumo();
}


////////////////////////////////////////////////////////////////////////////////////////
void xloop() {
  Serial.println();
}

long RCTime(int sensorIn){
   long duration = 0;
   pinMode(sensorIn, OUTPUT);     // Make pin OUTPUT
   digitalWrite(sensorIn, HIGH);  // Pin HIGH (discharge capacitor)
   delay(1);                      // Wait 1ms
   pinMode(sensorIn, INPUT);      // Make pin INPUT
   digitalWrite(sensorIn, LOW);   // Turn off internal pullups
   while(digitalRead(sensorIn)){  // Wait for pin to go LOW
      duration++;
   }
   return duration;
}
void loopSumo(){
  MoveForwardUntilPhoto(100); 
  if (RCTimePhoto(leftFrontPhoto)<10000 | RCTimePhoto(rightFrontPhoto)<5000) {
    MoveForward(-2);
    TurnRight(100);
  } else if (RCTimePhoto(leftBackPhoto)<50000) {
    MoveForward(2);
    }
  
//Move forward until QTI

//Move back 3

//Turn right 100

//
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void loopWOld() {
  debugWhiskers();
  int directions[] = {90,-90,-90,90,90,-90,-90,90,90,-90,-90,90,90,-90,-90,90};
  Stop();
  maze1(directions);
  exit;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Maze(){

  MoveForward(24);//1
  MoveForward(-1);
  TurnRight(90);
  MoveForward(24);//2
  MoveForward(-1);
  TurnRight(90);
  MoveForward(12);//3
  MoveForward(-1);
  TurnRight(-90);
  MoveForward(12);//4
  MoveForward(-1);
  TurnRight(-90);
  MoveForward(24);//5
  MoveForward(-1);
  TurnRight(90);
  MoveForward(48);//6
  MoveForward(-1);
  TurnRight(20);
  MoveForward(12);//7
  MoveForward(-1);
  TurnRight(-20);
  MoveForward(12);//8
  MoveForward(-1);
  TurnRight(90);
  MoveForward(24);//9
  MoveForward(-1);
  TurnRight(90);
  MoveForward(12);//10
  MoveForward(-1);
  TurnRight(-20);
  MoveForward(12);//11
  Stop;

}

void maze1(int directions[]){
  for (int i = 0; i < sizeof(directions)/2; i++) {
    MoveForwardUntilWhisker(50);
    delay(50);
    MoveForward(-1);
    TurnRight(directions[i]);
    Serial.println(directions[i]);
  }
}
long debugQTI() {
  return RCTime(8);
}
void debugWhiskers() {
  if(TestWhiskers()){Serial.println("TRUE");};
}

void debugMoveInches() {
  MoveForward(-1);
  Stop();
  WaitForWhiskers();
  MoveForward(-1);
  Stop();
  WaitForWhiskers();
}
void debugPhoto(){
  Serial.println("TestPhoto");
  TestPhoto();
}

void Stop(){
    Serial.println("Stop");
    servoLeft.writeMicroseconds(servoZero);
    servoRight.writeMicroseconds(servoZero);  
    delay(50);
}

bool TestWhiskers() {
  return digitalRead(LeftWhisker)+digitalRead(RightWhisker) < 1;
}
bool TestWhisker() {
  return digitalRead(LeftWhisker)+digitalRead(RightWhisker) < 2;
}
bool TestQTIs() {
  return RCTime(9)<500 | RCTime(8)<500;
}
bool TestQTI() {
  long rc = RCTime(8)<1000;
  Serial.println(rc);
  return rc;
}
void TurnRight(int degrees){
  Serial.println(degrees);
  int millisecondsToRun = map(abs(degrees),0,180,0,HalfTurnMilliseconds);
  Stop();
  if (degrees < 0) {
    servoLeft.writeMicroseconds(servoZero - 100);
    servoRight.writeMicroseconds(servoZero - 100);  
  } else {
    servoLeft.writeMicroseconds(servoZero + 100);
    servoRight.writeMicroseconds(servoZero + 100);  
}
  delay(millisecondsToRun);
  Stop();
}

void WaitForWhiskers(){
  Serial.println("WaitForWhiskers");
  while(TestWhiskers() == false){
    delay(100);
  }
  Serial.println(
"WaitForWhiskers DONE");
}

void MoveForwardUntilWhiskers(int SpeedPercent){
  Serial.println("MoveForwardUntilWhisker");
  int speedFrequency = map(SpeedPercent, 0, 100, 0, servoMax);
  while (TestWhiskers() == false){
    servoLeft.writeMicroseconds(servoZero + speedFrequency);
    servoRight.writeMicroseconds(servoZero - speedFrequency);
    delay(50);
  }
  Serial.println("MoveForwardUntilWhisker DONE");
}
void MoveForwardUntilWhisker(int SpeedPercent){
  Serial.println("MoveForwardUntilWhisker");
  int speedFrequency = map(SpeedPercent, 0, 100, 0, servoMax);
  while (TestWhisker() == false){
    servoLeft.writeMicroseconds(servoZero + speedFrequency);
    servoRight.writeMicroseconds(servoZero - speedFrequency);
    delay(50);
  }
  Serial.println("MoveForwardUntilWhisker DONE");
}

void MoveForwardUntilQTIs(int SpeedPercent){
  Serial.println("MoveForwardUntilQTI");
  int speedFrequency = map(SpeedPercent, 0, 100, 0, servoMax);
  while (TestQTIs() == false){
    servoLeft.writeMicroseconds(servoZero + speedFrequency);
    servoRight.writeMicroseconds(servoZero - speedFrequency);
    delay(50);
  }
  Serial.println("MoveForwardUntilWhisker DONE");
}
void MoveForwardUntilQTI(int SpeedPercent){
  Serial.println("MoveForwardUntilWhisker");
  int speedFrequency = map(SpeedPercent, 0, 100, 0, servoMax);
  while (TestQTI() == false){
    servoLeft.writeMicroseconds(servoZero + speedFrequency);
    servoRight.writeMicroseconds(servoZero - speedFrequency);
    delay(50);
  }
  Serial.println("MoveForwardUntilWhisker DONE");
}
void MoveForward(int inches){
  Serial.print("MoveForward at 10% for "); Serial.print(inches); Serial.println(" inches");
  if (inches < 0) {
    int millisecondsToRun = (0 - inches) * 700;
    servoLeft.writeMicroseconds(servoZero - 70);
    servoRight.writeMicroseconds(servoZero + 70);
    delay(millisecondsToRun);
  } else {
    int millisecondsToRun = inches * 700;
    servoLeft.writeMicroseconds(servoZero + 70);
    servoRight.writeMicroseconds(servoZero - 70);
    delay(millisecondsToRun);
  }
  Serial.println("MoveForward DONE");
}
void MoveForwardNumber(long milliseconds,int speed){
  Serial.print("MoveForward at 10% for "); Serial.print(inches); Serial.println(" inches");
  if (inches < 0) {
    servoLeft.writeMicroseconds(servoZero - speed);
    servoRight.writeMicroseconds(servoZero + speed);
    delay(milliseconds);
  } else {
    int millisecondsToRun = inches * 200;
    servoLeft.writeMicroseconds(servoZero + 70);
    servoRight.writeMicroseconds(servoZero - 70);
    delay(millisecondsToRun);
  }
  Serial.println("MoveForward DONE");
}
bool TestPhotos() {
    return RCTimePhoto(leftBackPhoto)<50000 | RCTimePhoto(leftFrontPhoto)<10000 | RCTimePhoto(rightFrontPhoto)<5000;


}
bool TestPhoto() {
  //return RCTime(1)<500;
  Serial.print("TestPhoto FrontLeft: ");
  Serial.println(RCTimePhoto(leftFrontPhoto));
  Serial.print("TestPhoto FrontRight: ");
  Serial.println(RCTimePhoto(rightFrontPhoto));
  Serial.print("TestPhoto RearLeft: ");
  Serial.println(RCTimePhoto(leftBackPhoto));
  Serial.print("TestPhoto RearRight: ");
  Serial.println(RCTimePhoto(rightBackPhoto));
}
void MoveForwardUntilPhoto(int SpeedPercent){
  Serial.println("MoveForwardUntilPhoto");
  int speedFrequency = map(SpeedPercent, 0, 100, 0, servoMax);
  while (TestPhotos() == false){
    servoLeft.writeMicroseconds(servoZero + speedFrequency);
    servoRight.writeMicroseconds(servoZero - speedFrequency);
    delay(50);
  }
  Stop;
  Serial.println("MoveForwardUntilPhoto DONE");
}
long RCTimePhoto(int pin){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(3);
  pinMode(pin, INPUT);
  digitalWrite(pin, LOW);
  long time  = micros();
  while(digitalRead(pin));
  time = micros() - time;
  return time;
}
