/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/

#ifndef PulsePump_h
#include "SimplePump.h"
#define PulsePump_h

class PulsePump: public SimplePump
{
public:
  PulsePump(bool (*startFunc)(int),bool (*stopFunc)(),bool (*changeSpeedFunc)(int),bool (*initFunc)()=nullptr, int initialSpeed=100);

  bool start(int speed = 100);
  bool stop();
  bool changeSpeed(int speed);
  unsigned long getDurationSinceLastChange();
  bool init();

private:
  unsigned long sinceLastPulse;
  unsigned long pulseDuration;
  unsigned long pulseInterval;
};

#endif