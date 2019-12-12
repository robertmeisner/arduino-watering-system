/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/
#ifndef Switch_h
#include "SimpleSwitch.h"
#define SimplePump_h

class Light : public SimpleSwitch
{
public:
    Light(int pin);

    bool isOn();
    getDurationIsOn()
    SwitchStates state = SwitchStates::STATE_OFF;

private:
    int _pin;
    unsigned long wateringCycleChrono;
    bool startTimer();
    bool stopTimer();
    SwitchStates nextState(SwitchCommand p);
};
Light::Light(int pin):SimpleSwitch(int pin){

}
bool Light::turnOn()
{
    if (SimpleSwitch::turnOn())
    {
        return this->startTimer();
    }
}
#endif