#include "Arduino.h"
#include "Pump.h"

Pump::Pump(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}
bool Pump::start(int speed){
    return 0;
}
bool Pump::stop(int speed){
    return 0;
}
int Pump::getTimeRunning(){
    return 0;
}
void Pump::nextState(){
    this->state
}