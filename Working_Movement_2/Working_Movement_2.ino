// Robotics with the BOE Shield - ForwardLeftRightBackward
// Move forward, left, right, then backward for testing and tuning.

#include <Servo.h>                           

Servo servoLeft;
Servo servoRight;

int servoPinLeft = 13;
int servoPinRight = 12;
int whiskerPinLeft = 5;
int whiskerPinRight = 7;
int lightPinLeft = 8;
int lightPinRight = 6;
int irHeadlightLeft = 9;
int irHeadlightRight = 2;
int irReceiverLeft = 10;
int irReceiverRight = 3;


void setup()                                
{ 
  StartupTones();
  AttachServos(servoPinLeft, servoPinRight);
  //AttachWhiskers(whiskerPinLeft, whiskerPinRight);
  //AttachLightSensors(lightPinLeft, lightPinRight);
  AttachIrSensors (irHeadlightLeft, irReceiverLeft, irHeadlightRight, irReceiverRight);
  
}  

void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
  //MovementTests();
  //RoamWithWhiskers();
  //RoamWithLightSensors();
  RoamWithIr();
} 


void RoamWithIr()                                  // Main loop auto-repeats
{
  int irLeft = irDetect(irHeadlightLeft, irReceiverLeft, 38000);       // Check for object on left
  int irRight = irDetect(irHeadlightRight, irReceiverRight, 38000);       // Check for object on right

  if((irLeft == 0) && (irRight == 0))        // If both sides detect
  {
    MoveBackward(50,1000);                          // Back up 1 second
    PivotCounterClockwise(50,800);                           // Turn left about 120 degrees
  }
  else if(irLeft == 0)                       // If only left side detects
  {
    MoveBackward(50,1000);                          // Back up 1 second
    PivotClockwise(50,400);                          // Turn right about 60 degrees
  }
  else if(irRight == 0)                      // If only right side detects
  {
    MoveBackward(50,1000);                          // Back up 1 second
    PivotCounterClockwise(50,400);                           // Turn left about 60 degrees
  }
  else                                       // Otherwise, no whisker contact
  {
    MoveForward(50,20);                             // Forward 1/50 of a second
  }
}

void RoamWithLightSensors () {
  float tLeft = float(rcTime(lightPinLeft));            // Get left light & make float
  float tRight = float(rcTime(lightPinRight));           // Get right light & make float
  
  float ndShade;                             // Normalized differential shade
  ndShade = tRight / (tLeft+tRight) - 0.5;   // Calculate it and subtract 0.5

  int speedLeft, speedRight;                 // Declare speed variables
  
  if (ndShade > 0.0)                         // Shade on right?
  {                                          // Slow down left wheel
    speedLeft = int(200.0 - (ndShade * 1000.0));
    speedLeft = constrain(speedLeft, -200, 200);
    speedRight = 200;                        // Full speed right wheel
  } 
  else                                       // Shade on Left?
  {                                          // Slow down right wheel
    speedRight = int(200.0 + (ndShade * 1000.0));
    speedRight = constrain(speedRight, -200, 200);
    speedLeft = 200;                         // Full speed left wheel
  }  

  maneuver(speedLeft, speedRight, 20); 
}


int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}  

long rcTime(int pin)                         // rcTime measures decay at pin
{
  pinMode(pin, OUTPUT);                      // Charge capacitor 
  digitalWrite(pin, HIGH);                   // ..by setting pin ouput-high
  delay(5);                                  // ..for 5 ms
  pinMode(pin, INPUT);                       // Set pin to input
  digitalWrite(pin, LOW);                    // ..with no pullup
  long time  = micros();                     // Mark the time
  while(digitalRead(pin));                   // Wait for voltage < threshold
  time = micros() - time;                    // Calculate decay time
  return time;                               // Returns decay time
}

void RoamWithWhiskers ()
{
  byte wLeft = digitalRead(whiskerPinLeft);  
  byte wRight = digitalRead(whiskerPinRight);

  if((wLeft == 0) && (wRight == 0))      
  {
    MoveBackward(50,1000);
    PivotCounterClockwise(50,800);                           
  }
  else if(wLeft == 0)                      
  {
    MoveBackward(50,1000);                          
    PivotClockwise(50,400);                         
  }
  else if(wRight == 0)                      
  {
    MoveBackward(50,1000);                          // Back up 1 second
    PivotCounterClockwise(50,400);                           // Turn left about 60 degrees
  }
  else                                       // Otherwise, no whisker contact
  {
    MoveForward(50,20);                             // Forward 1/50 of a second
  }
}


void MovementTests ()
{
  MoveForward(100, 2000);
  PivotCounterClockwise(100,600);
  PivotClockwise(100,600);
  MoveBackward(100,2000);
}


void AttachIrSensors (int leftHeadlight, int leftReceiver, int rightHeadlight, int rightReceiver)
{
  pinMode(leftReceiver, INPUT);  pinMode(leftHeadlight, OUTPUT);   // Left IR LED & Receiver
  pinMode(rightReceiver, INPUT);  pinMode(rightHeadlight, OUTPUT);    // Right IR LED & Receiver 
}

void AttachLightSensors (int leftPin, int rightPin) 
{
  
}

void AttachWhiskers(int leftPin, int rightPin) 
{
  pinMode(whiskerPinLeft, INPUT);
  pinMode(whiskerPinRight, INPUT);
}


void AttachServos (int left,int right)
{
  servoLeft.attach(left);                   
  servoRight.attach(right);                
}

void StartupTones()
{
  tone(4, 3000, 1000);
  delay(1000);
}

void MoveForward(int speed, int time)
{
  servoLeft.writeMicroseconds(1500 + speed * 2);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1500 - speed * 2);        // Right wheel clockwise
  delay(time);
}

void MoveBackward(int speed, int time)
{
  servoLeft.writeMicroseconds(1500 - speed * 2);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1500 + speed * 2);        // Right wheel clockwise
  delay(time);
}

void PivotClockwise(int speed, int time)
{
  servoLeft.writeMicroseconds(1500 + speed * 2);         // Left wheel clockwise
  servoRight.writeMicroseconds(1500 + speed * 2);        // Right wheel clockwise
  delay(time);
}

void PivotCounterClockwise(int speed, int time)
{
  servoLeft.writeMicroseconds(1500 - speed * 2);         // Left wheel clockwise
  servoRight.writeMicroseconds(1500 - speed * 2);        // Right wheel clockwise
  delay(time);
}

// maneuver function
void maneuver(int speedLeft, int speedRight, int msTime)
{
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
  if(msTime==-1)                                   // if msTime = -1
  {                                  
    servoLeft.detach();                            // Stop servo signals
    servoRight.detach();   
  }
  delay(msTime);                                   // Delay for msTime
}
