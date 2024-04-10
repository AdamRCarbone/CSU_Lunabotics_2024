#ifndef _CSULUNABOTICSACTUATOR_H_INCLUDED
#include "CSULunaboticsActuator.h"
#endif

void initialize_actuator (linearActuator *actuator, int extendPin, int retractPin)
{

  actuator->extendPin = extendPin;
  actuator->retractPin = retractPin;

  pinMode (extendPin, OUTPUT);
  pinMode (retractPin, OUTPUT);

  actuator->direction = STOP;

}

void actuate (linearActuator *actuator)
{
  switch(actuator->direction) {
    case EXTEND:
      digitalWrite(actuator->extendPin, HIGH);
      digitalWrite(actuator->retractPin, LOW);
      break;
    case STOP:
      digitalWrite(actuator->extendPin, LOW);
      digitalWrite(actuator->retractPin, LOW);
      break;
    case RETRACT:
      digitalWrite(actuator->retractPin, HIGH);
      digitalWrite(actuator->extendPin, LOW);
      break;
  }
}

void set_actuator_state (linearActuator *actuator, int triState)
{
  switch (triState)
  {
    case 0:
      actuator->direction = RETRACT;
      break;
    case 1:
      actuator->direction = STOP;
      break;
    case 2:
      actuator->direction = EXTEND;
      break;
  }
}