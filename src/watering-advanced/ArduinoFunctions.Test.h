#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#ifndef ArduinoFunctionsTest_h
#define ArduinoFunctionsTest_h
Adafruit_ADS1115 ads;
float Sensor1ReadFunc()
{
    return 10;
}
float Sensor2ReadFunc()
{
    return 10;
}
bool initPumpFunc()
{
    return true;
}
bool startPumpFunc(int speed)
{
    return true;
}
bool stopPumpFunc()
{
    return true;
}
bool changePumpSpeedFunc(int speed)
{
    return true;
}
bool lightOnFunc()
{
    return true;
}
bool lightOffFunc()
{
    return true;
}
bool lightInitFunc()
{
    return true;
}
#endif