/*
A library to control a DC motor using a PWM driver board
Written for the CSU robot for the 2024 NASA Lunabotics Competition
*/

#ifndef _CSULUNABOTICSSWITCH_H_INCLUDED
#define _CSULUNABOTICSSWITCH_H_INCLUDED
#endif

struct two_pos_switch
{
  int pin;
  bool state;
};

void initialize_switch (two_pos_switch *sw, int pin);

void set_state (two_pos_switch *sw, bool b);

void on (two_pos_switch *sw);

void off (two_pos_switch *sw);
