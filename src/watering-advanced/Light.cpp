#include "Light.h"

Light::Light(int pin):SimpleSwitch(pin){

};
bool Light::turnOn()
{
    if (SimpleSwitch::turnOn())
    {
        return this->startTimer();
    }
};
 bool Light::isOn(){

 }
bool Light::startTimer(){
  
};
int Light::getDurationSinceLastChange(){

}

bool Light::stopTimer(){

}
SwitchStates Light::nextState(SwitchCommand p){

}