#include "Light.h"
#include "Arduino.h"
#include "SwitchStateMachine.h"
#include "CustomLog.h"
Light::Light(int pin) : SimpleSwitch(pin){};
void Light::init()
{
    cLog("Initiating Light");
    SimpleSwitch::init();
}
bool Light::turnOn()
{
    if (SimpleSwitch::turnOn())
    {
        return this->restartTimer();
    }
};
bool Light::isOn()
{
    return this->state == SwitchStates::SWITCH_ON;
}
bool Light::restartTimer()
{
    this->sinceLastChangeChrono = millis();
};
unsigned long Light::getDurationSinceLastChange()
{
    return millis() - this->sinceLastChangeChrono;
}