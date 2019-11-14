/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/
#ifndef Pump_h
#include "state-machine/PumpStateMachine.h"
#define Pump_h

enum PumpStates
{
  STATE_OFF,
  STATE_ON
};
enum PumpCommand
{
  COMMAND_START,
  COMMAND_STOP

};
class Pump : public PumpStateMachine
{
public:
  Pump(int pin);

  bool start();
  bool stop();
  int getTimeRunning();

  PumpStates state = PumpStates::STATE_OFF;

private:
  int _pin;
  void nextState();
};

#endif