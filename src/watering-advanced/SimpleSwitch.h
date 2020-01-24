/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/
#ifndef SimpleSwitch_h
#include "SwitchStateMachine.h"
#define SimpleSwitch_h


class SimpleSwitch : public SwitchStateMachine
{
public:
  SimpleSwitch(int pin);

  bool turnOn();
  bool turnOff();

private:
  int _pin;
};



#endif