#ifndef _CSULUNABOTICSSWITCH_H_INCLUDED
#include "CSULunaboticsSwitch.h"
#endif


void initialize_switch (two_pos_switch *sw, int pin)
{
  pinMode (pin, OUTPUT);
  sw->pin = pin;
  
}

void do_on_off (two_pos_switch *sw)
{
  if (sw->state)
    on (sw);
  else 
    off (sw);
}

void set_state (two_pos_switch *sw, bool b)
{
  sw->state = b;
}

void on (two_pos_switch *sw)
{
  digitalWrite (sw->pin, HIGH);
}

void off (two_pos_switch *sw)
{
  digitalWrite (sw->pin, LOW);
}