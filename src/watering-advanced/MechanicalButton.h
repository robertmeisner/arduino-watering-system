/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/

#ifndef MechanicalButton_h
#define MechanicalButton_h

#include "state-machine/ButtonStateMachine.h"
#include "Arduino.h"
#include <EdgeDebounceLite.h>
#include "MechanicalButton.h"

class MechanicalButton : public ButtonStateMachine
{
public:
  MechanicalButton(int pin, ButtonModes mode);
  ButtonModes buttonMode = ButtonModes::MODE_PULLDOWN;
  ButtonStates state = ButtonStates::STATE_OPEN;
  void setupInterruptHandler(uint8_t irq_pin, void (*interruptFunction)(void), int value);
  void handleInterrupt(void);

private:
  int _pin;
  void nextState(ButtonCommand p);
};

MechanicalButton::MechanicalButton(int pin, ButtonModes mode) : _pin(pin), buttonMode(mode)
{}
void init()
{
  pinMode(this->_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(this->_pin), this->buttonInteracted, CHANGE);
}
void MechanicalButton::setupInterruptHandler(uint8_t irq_pin, void (*ISR)(void), int value)
{
  attachInterrupt(digitalPinToInterrupt(irq_pin), ISR, value);
}
inline void MechanicalButton::handleInterrupt(void)
{
  EdgeDebounceLite debounce;
  byte pinIs = debounce.pin(this->_pin); //Debounce the pin
  if (this->buttonMode == ButtonModes::MODE_PULLUP)
    pinIs = !pinIs; //Reverse the read if Pullup
  switch (this->state)
  {
  case (SwitchStates::STATE_CLOSED):
    if (pinIs == LOW)                                   //If pin is LOW
      this->nextState(ButtonCommand::COMMAND_RELEASED); //Change state to IS_FALLING
    break;
  case (SwitchStates::STATE_IS_FALLING):
    //Do something (The switch has been clicked)
    this->nextState(ButtonCommand::COMMAND_RELEASED); //Change state to IS_OPEN (Not falling anymore)
    break;
  case (SwitchStates::STATE_OPEN):
    if (pinIs == HIGH)                                 //If pin is HIGH
      this->nextState(ButtonCommand::COMMAND_PRESSED); //Change state to IS_RISING
    break;
  case (SwitchStates::STATE_RISING):
    this->nextState(ButtonCommand::COMMAND_PRESSED); //Change state to IS_CLOSED (Not rising anymore)
    break;

  default:
    break;
  }
}
ButtonStates MechanicalButton::nextState(ButtonCommand command)
{
  ButtonStates nextState = this->state;
  switch (command)
  {
  case ButtonCommand::COMMAND_PRESSED:
    if (this->state == ButtonStates::STATE_OPEN)
      nextState = ButtonStates::STATE_RISING;
    else if (this->state == ButtonStates::STATE_RISING)
      nextState = ButtonStates::STATE_CLOSED;
    break;
  case ButtonCommand::COMMAND_RELEASED:
    if (this->state == ButtonStates::STATE_OPEN)
      nextState = ButtonStates::STATE_RISING;
    else if (this->state == ButtonStates::STATE_RISING)
      nextState = ButtonStates::STATE_CLOSED;
    break;
    break;

  default:
    break;
  }
  this->state = nextState;
  return this->state;
}

MoistureSensor::MoistureSensor(int pin)
{
  //set all values to full wet
  for (byte j = 0; j < MOISTURE_READINGS_COUNT; j++)
  {
    this->_moistureReadings[j] = 100;
  }
  _pin = pin;
}

int MoistureSensor::read()
{
  if (this->nextState(MoistureSensorCommand::COMMAND_READ) == MoistureSensorStates::STATE_READING)
  {
    this->_moistureReadingNumber++;

    int value = analogRead(this->_pin);  // Read analog value
    value = constrain(value, 400, 1023); // Keep the ranges!
    value = map(value, 400, 1023, 100, 0);
    this->_moistureReadings[this->_moistureReadingNumber - 1] = value;

    if (this->_moistureReadingNumber > 7)
    {
      this->_moistureReadingNumber = 0;
    }

    this->nextState(MoistureSensorCommand::COMMAND_FINISHED_READ);
    return value;
  }
  return -1;
}

int MoistureSensor::readAvg()
{
  int avg = 0;
  for (byte j = 0; j < MOISTURE_READINGS_COUNT; j++)
  {
    avg += this->_moistureReadings[j];
  }

  return avg / MOISTURE_READINGS_COUNT;
}
MoistureSensorStates MoistureSensor::nextState(MoistureSensorCommand command)
{
  switch (this->state)
  {
  case MoistureSensorStates::STATE_IDLE:
    if (MoistureSensorCommand::COMMAND_READ)
    {
      this->state = MoistureSensorStates::STATE_READING;
    }
    break;
  case MoistureSensorStates::STATE_READING:
    if (MoistureSensorCommand::COMMAND_FINISHED_READ)
    {
      this->state = MoistureSensorStates::STATE_IDLE;
    }
    break;

  default:
    break;
  }
  return this->state;
}
#endif