/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/

#ifndef MechanicalButton_h
#define MechanicalButton_h
#include "ButtonStateMachine.h"
#include "Arduino.h"

class MechanicalButton : public ButtonStateMachine
{
public:
  MechanicalButton(int pin, ButtonModes mode=ButtonModes::MODE_PULLDOWN);
  ButtonModes buttonMode = ButtonModes::MODE_PULLDOWN;
  void setupInterruptHandler(uint8_t irq_pin, void (*interruptFunction)(void), int value);
  void handleInterrupt(void);
  void init();
  void tick();
private:
  uint8_t _pin;
  ButtonStates nextState(ButtonCommand p);
};


#endif