#include "SimpleSwitch.h"
#include "Arduino.h"
//IMPLEMENTATION 
SimpleSwitch::SimpleSwitch(int pin):SwitchStateMachine(), _pin(pin)
{
  pinMode(pin, OUTPUT);
}
bool SimpleSwitch::turnOff()
{
  SwitchStates stateTmp = this->state;
  digitalWrite(this->_pin, LOW);
  this->nextState(SwitchCommand::COMMAND_OFF);
  return true;
}
bool SimpleSwitch::turnOn()
{
  SwitchStates stateTmp = this->state;
  digitalWrite(this->_pin, HIGH);
  return stateTmp != this->nextState(SwitchCommand::COMMAND_ON);
}