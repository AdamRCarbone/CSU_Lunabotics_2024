/*
UPDATED CODE TO RUN STEPPER MOTORS ALONG WITH LINEAR ACTUATOR ****NOT TESTED****
*/

#include <SPI.h>
#include <Wire.h>
#include "CSULunaboticsActuator.h"
#include "CSULunaboticsStepper.h"

long currTime;

/*struct stepperMotor
{
  //pin that connects to the PUL + part of the stepper controller
  int pulsePin;

  //pin that connects to the DIR + part of the stepper controller 
  int directionPin;

  //time between half-steps of the motor, see the function definition of halfPulse
  int pulseDuration;

  //holds the direction of the motor, HIGH is one way, LOW is the other
  bool direction;

  //Stores the time of the most recent half step
  long lastStep;

  //Holds the state of the last step, since one "half step" turns it on then the next "half step" turns it off
  int stepState;
};*/

stepperMotor rightMotor, leftMotor;
linearActuator actuator;

void setup() {

  initialize_stepper (&rightMotor, /*pulse pin*/ 3, /*direction pin*/ 4);
  initialize_stepper (&leftMotor, /*pulse pin*/ 9, /*direction pin*/ 8);
  initialize_actuator (&actuator, /*extend pin*/ 12, /*retract pin*/ 11);
  
  Serial.begin(9600);

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

void loop() {
  currTime = micros ();

  step (&rightMotor, currTime);
  step (&leftMotor, currTime);
}

void receiveEvent(int howMany)
{
  char buffer[10];
  int i = 0;
  while (Wire.available())
    buffer[i++] = Wire.read();
  buffer[i] = '\0';
  //Serial.println(buffer);
  char rightSpeed[3];
  char leftSpeed[3];
  char triState;
  char diggingMotor;
  
  rightSpeed[0] = buffer[0];
  rightSpeed[1] = buffer[1];
  rightSpeed[2] = '\0';
  leftSpeed[0] = buffer[2];
  leftSpeed[1] = buffer[3];
  leftSpeed[2] = '\0';
  triState = buffer[4] - '0';
  diggingMotor = buffer[5];
  set_motor_speed (&rightMotor, atoi (rightSpeed) - 50);
  set_motor_speed (&leftMotor, atoi (leftSpeed) - 50);

  set_actuator_state (&actuator, int (triState));
  actuate (&actuator);
}