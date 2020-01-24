/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/

#ifndef SimplePumps_h
#include "PumpStateMachine.h"
#define SimplePumps_h

class SimplePump : public PumpStateMachine
{
public:
  SimplePump(int pin, int initialSpeed);

  bool start(int speed = 100);
  bool stop();
  bool changeSpeed(int speed);
  int getTimeRunning();
  int speed = 0;

private:
  int _pin;
  PumpStates nextState(PumpCommand p);
};


#endif