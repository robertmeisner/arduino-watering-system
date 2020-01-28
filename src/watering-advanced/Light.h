/*
  Created by Robert Meisner, 2020.
  Released into the public domain.
*/
#ifndef Light_h
#include "SimpleSwitch.h"
#define Light_h 

class Light : public SimpleSwitch
{
public:
    Light(int pin);
    void init();
    bool turnOn();
    bool isOn();
    unsigned long getDurationSinceLastChange();
    SwitchStates state = SwitchStates::SWITCH_OFF;

private:
    int _pin;
    unsigned long sinceLastChangeChrono;
    bool restartTimer();
};

#endif
