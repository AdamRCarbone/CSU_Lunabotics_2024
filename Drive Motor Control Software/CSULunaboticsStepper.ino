#ifndef _CSULUNABOTICSSTEPPER_H_INCLUDED
#include "CSULunaboticsStepper.h"
#endif

void initialize_stepper (stepperMotor *motor, int pulsePin, int directionPin)
{

  motor->pulsePin = pulsePin;
  motor->directionPin = directionPin;
  motor->pulseDuration = 500;
  motor->direction = LOW;
  motor->stepState = 0;
  motor->lastStep = 0;

  pinMode (pulsePin, OUTPUT);
  pinMode (directionPin, OUTPUT);

}

void set_motor_speed (stepperMotor *motor, int speed)
{

  if (speed < 0)
    motor->direction = LOW;
  else
    motor->direction = HIGH;
  motor->pulseDuration = map (abs (speed), 0, 50, 500, 150);
}

void step (stepperMotor *motor, long currTime)
{
  if (motor->pulseDuration > 450)
    return;
  if (currTime - motor->lastStep > motor->pulseDuration)
    halfPulse (motor);
}

void halfPulse (stepperMotor *motor)
{
  motor->stepState = !motor->stepState;
  digitalWrite (motor->pulsePin, motor->stepState);
  digitalWrite (motor->directionPin, motor->direction);
  motor->lastStep = currTime;
}
