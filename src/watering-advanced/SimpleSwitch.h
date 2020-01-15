/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/
#ifndef SimpleSwitch_h
#include "state-machine/SwitchStateMachine.h"
#define SimpleSwitch_h

#include "Arduino.h";

class SimpleSwitch : public SwitchStateMachine
{
public:
  SimpleSwitch(int pin);

  bool turnOn();
  bool turnOff();

private:
  int _pin;
};

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

#endif