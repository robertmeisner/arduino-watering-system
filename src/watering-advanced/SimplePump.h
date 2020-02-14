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
  unsigned long getDurationSinceLastChange();

  void init();

private:
  int _pin;
  int _speed = 0;
  unsigned long sinceLastChangeChrono;
};

#endif