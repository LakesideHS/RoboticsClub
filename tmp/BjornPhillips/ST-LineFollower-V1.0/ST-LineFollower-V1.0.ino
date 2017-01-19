/*

Simple line follower program, using 4 SimplyTronics Line Follower Sensors, connected to a ST EDU 
or ST-EDU-S board. 
This basic program demonstrates how the robot can follow a line, without optimization.
For competitions, students can take this program and modify it to increase line following 
efficiency. 

Connection table for Line Follower Sensors:
ST-EDU/S          Sensor
P8                Far left
P9                Mid left
P10               Mid right
P11               Far right

Connection table for Servos:
ST-EDU/S         Servo
P13              Left servo
P12              Right servo

This example code is based on code writen by Parallax for the QTI sensors.

*/

#include <Servo.h>                           // Use the Servo library (included with Arduino IDE)  

Servo servoL;                                // Define the left and right servos
Servo servoR;

// Perform these steps with the Arduino is first powered on
void setup()
{
  servoL.attach(13);                         // Attach (programmatically connect) servos to pins on Arduino
  servoR.attach(12);

  pinMode(8, INPUT);                         // Set line follower pins to inputs
  pinMode(9, INPUT);                          
  pinMode(10, INPUT);
  pinMode(11, INPUT); 
}

// This code repeats indefinitely
void loop()
{
  byte LF_8 = digitalRead(8);              // Copy Line Follower Sensor value to byte variables
  byte LF_9 = digitalRead(9);
  byte LF_10 = digitalRead(10);
  byte LF_11 = digitalRead(11);              
  
  
  // Determine how to steer based on state of the two line follower sensors
  int vL, vR;

    if ((LF_9 == 1) && (LF_10 == 1)) {     // If both center line sensors see the line                    
      vL = 40;                             // forward high speed
      vR = 40;
    }
    else if (LF_9 == 1) {                  // If second left sensor sees the line     
      vL = 0;                              // vear left
      vR = 30;
    }
    else if (LF_10 == 1) {                 // If second right sensor sees the line   
      vL = 30;                             // vear right
      vR = 0;
    }
    else if (LF_8 == 1)  {                 // If leftmost sensor sees the line        
      vL = -20;                            // make a sharp turn left
      vR = 40;
    }
     else if (LF_11 == 1)  {               // If rightmost sensor sees the line        
      vL = 40;                             // make a sharp turn right
      vR = -20;
    }
     else   {                              // If no sensor detects a line
      vL = 0;                              // stop motors
      vR = 0;                             
    }
  
  servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1500 - vR);
  
  delay(50);                                // Delay for 50 milliseconds (1/20 second)
}

