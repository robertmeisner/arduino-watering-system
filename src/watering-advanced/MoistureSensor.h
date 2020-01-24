/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/
#include "StateMachine.h"
#ifndef MOISTURE_READINGS_COUNT
#define MOISTURE_READINGS_COUNT 8
#endif
#ifndef MoistureSensor_h
#define MoistureSensor_h

enum MoistureSensorStates
{
  STATE_READING,
  STATE_IDLE
};
enum MoistureSensorCommand
{
  COMMAND_READ,
  COMMAND_FINISHED_READ
};

class MoistureSensor:StateMachine
{
public:
  MoistureSensor(int pin);

  int read();
  int readAvg();
  void init();
  MoistureSensorStates moistureState = MoistureSensorStates::STATE_IDLE;

private:
  MoistureSensorStates state = MoistureSensorStates::STATE_IDLE;
  int _pin;
  int _moistureReadingNumber = 0;
  int _moistureReadings[MOISTURE_READINGS_COUNT];
  MoistureSensorStates nextState(MoistureSensorCommand p);
};

#endif