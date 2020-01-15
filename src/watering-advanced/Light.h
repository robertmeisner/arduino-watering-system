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
    bool turnOn();
    bool isOn();
    int getDurationIsOn();
    SwitchStates state = SwitchStates::SWITCH_OFF;

private:
    int _pin;
    unsigned long wateringCycleChrono;
    bool startTimer();
    bool stopTimer();
    SwitchStates nextState(SwitchCommand p);
};
Light::Light(int pin):SimpleSwitch(pin){

};
bool Light::turnOn()
{
    if (SimpleSwitch::turnOn())
    {
        return this->startTimer();
    }
};
bool Light::startTimer(){
  
};
#endif
