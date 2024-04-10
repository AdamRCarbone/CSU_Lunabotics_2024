/* 
A small library to easily control a linear actuator.
Written for the CSU robot for the 2024 NASA Lunabotics Competition
This code really controls the relay which, in turn, controls the actuator, 
but to simplify the code, this program says it is controlling the actuator itself
*/

#ifndef _CSULUNABOTICSACTUATOR_H_INCLUDED
#define _CSULUNABOTICSACTUATOR_H_INCLUDED
#endif

/*
Used as expected, if state is EXTEND, actuator extends, etc.
*/
enum state
{
  EXTEND,
  STOP,
  RETRACT
};

/*
holds values relevant to linear actuator, pins and direction
*/
struct linearActuator
{
  //pin used to extend the actuator
  int extendPin;

  //pin used to retract the actuator
  int retractPin;

  //holds the direction that the actuator is moving 
  state direction;
};

/*
Initializes the actuator pins and the actuator state set to STOP
*/
void initialize_actuator (linearActuator *actuator, int extendPin, int retractPin);

/*
sets the state of the actuator until the next time this function is called,
this function makes sense to call in loop()
*/
void actuate (linearActuator *actuator);

/*
Sets the actuator state to EXTEND, STOP, or RETRACT based on tristate ranging from 0-2
*/
void set_actuator_state (linearActuator *actuator, int triState);
