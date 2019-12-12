/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "MoistureSensor.h"

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