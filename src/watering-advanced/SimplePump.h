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
  SimplePump(bool (*startFunc)(int),bool (*stopFunc)(),bool (*changeSpeedFunc)(int),bool (*initFunc)()=nullptr, int initialSpeed=100);

  bool start(int speed = 100);
  bool stop();
  bool changeSpeed(int speed);
  unsigned long getDurationSinceLastChange();

  bool init();

private:
   bool (*_startFunc)(int);
   bool (*_stopFunc)();
   bool (*_changeSpeedFunc)(int);
   bool (*_initFunc)();
  int _speed = 0;
  unsigned long sinceLastChangeChrono;
};

#endif