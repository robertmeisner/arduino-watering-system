/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/
#ifndef MoistureSensor_h
#define MoistureSensor_h

enum MoistureSensorStates
{
    STATE_READ,
    STATE_IDLE
};

class MoistureSensor
{
  public:
    MoistureSensor(int pin);

    int read();
    int readAvg();
    MoistureSensorStates moistureState = MoistureSensorStates::STATE_READ;

  private:
    int _pin;
    int _moistureReadingNumber = 0;
    int _moistureReadings[8] = {100, 100, 100, 100, 100, 100, 100, 100};
};

#endif