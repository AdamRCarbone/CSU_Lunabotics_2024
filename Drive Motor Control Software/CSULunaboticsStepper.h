/*
Brief library to control a stepper motors that we are using on the CSU 2024 Lunabotics competition robot
Calling a struct of this type a "stepper motor" is a little misleading as it is actually specific to the
motor controller but for simplicity sake I chose to write it this way.
*/

#ifndef _CSULUNABOTICSSTEPPER_H_INCLUDED
#define _CSULUNABOTICSSTEPPER_H_INCLUDED
#endif

/*
A structure to store the important values of a stepper motor
includes pins, time between steps, direction, etc
*/
struct stepperMotor
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
  bool stepState;
};

/*
Initializes "stepper motor" with some default values as well as the pulse pin
and the direction pin passed in
*/
void initialize_stepper (stepperMotor *motor, int pulsePin, int directionPin);

/*
Sets the speed of the motor, takes in a value from -49 to 49 *****SUBJECT TO CHANGE*****
the higher the absolute value of the speed, the faster the motors move, if motors move one way
*/
void set_motor_speed (stepperMotor *motor, int speed);

/*performs a half step of the motor
simply call it twice to do a full step.*/
void step (stepperMotor *motor);
