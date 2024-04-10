/*
UPDATED CODE TO RUN STEPPER MOTORS ALONG WITH LINEAR ACTUATOR ****NOT TESTED****
*/
#include <SPI.h>
#include <Wire.h>
#include "CSULunaboticsActuator.h"
#include "CSULunaboticsStepper.h"
#include "CSULunaboticsSwitch.h"

long currTime;

stepperMotor rightMotor, leftMotor;
linearActuator actuator;
two_pos_switch diggingMotor;

void setup() {

  initialize_stepper (&rightMotor, /*pulse pin*/ 3, /*direction pin*/ 4);
  initialize_stepper (&leftMotor, /*pulse pin*/ 5, /*direction pin*/ 6);
  initialize_actuator (&actuator, /*extend pin*/ 7, /*retract pin*/ 8);
  initialize_switch (&diggingMotor, 9);
  
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
  char digState;
  
  rightSpeed[0] = buffer[0];
  rightSpeed[1] = buffer[1];
  rightSpeed[2] = '\0';
  leftSpeed[0] = buffer[2];
  leftSpeed[1] = buffer[3];
  leftSpeed[2] = '\0';
  triState = buffer[4] - '0';
  digState = buffer[5] - '0';
  set_motor_speed (&rightMotor, atoi (rightSpeed) - 50);
  set_motor_speed (&leftMotor, atoi (leftSpeed) - 50);

  set_actuator_state (&actuator, int (triState));

  if (digState)
    set_state (&diggingMotor, true);
  else
    set_state (&diggingMotor, false);

  actuate (&actuator);
  do_on_off (&diggingMotor);
}