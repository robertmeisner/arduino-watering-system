#include "MoistureSensor.h"
#include "Arduino.h"
#include "CustomLog.h"
bool mockFunc()
{
  return true;
}
MoistureSensor::MoistureSensor(float readFunc(), bool initFunc())
{
  this->_readFunc = readFunc; 
  if (initFunc != nullptr)
    this->_initFunc = initFunc;
  else
    this->_initFunc = mockFunc;
}
float MoistureSensor::read()
{
  cLog("MoistureSensor::read()");
  if (this->nextState(MoistureSensorCommand::COMMAND_READ) == MoistureSensorStates::STATE_READING)
  {
    cLog("MoistureSensor::read() - inner");
    float value = 0;

    this->_moistureReadingNumber++;
    value = this->_readFunc(); // Read analog value

    this->_moistureReadings[this->_moistureReadingNumber - 1] = value;

    if (this->_moistureReadingNumber > 7)
    {
      this->_moistureReadingNumber = 0;
    }

    this->nextState(MoistureSensorCommand::COMMAND_FINISHED_READ);
    return this->_moistureReadings[this->_moistureReadingNumber - 1];
  }
  return -1;
}

int MoistureSensor::readAvg()
{
  cLog("Reading the sensor average");
  int avg = 0;
  for (byte j = 0; j < MOISTURE_READINGS_COUNT; ++j)
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
    if (command == MoistureSensorCommand::COMMAND_READ)
    {
      this->state = MoistureSensorStates::STATE_READING;
    }
    break;
  case MoistureSensorStates::STATE_READING:

    if (command == MoistureSensorCommand::COMMAND_FINISHED_READ)
    {
      this->state = MoistureSensorStates::STATE_IDLE;
    }
    break;

  default:
    break;
  }
  return this->state;
}

bool MoistureSensor::init()
{
  if (this->_initFunc())
  {
    //set all values to full wet
    for (byte j = 0; j < MOISTURE_READINGS_COUNT; j++)
    {
      this->_moistureReadings[j] = 100.0;
    }
    return true;
  }
  return false;
}