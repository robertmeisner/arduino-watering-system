#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#ifndef ArduinoFunctions_h
#define ArduinoFunctions_h 
Adafruit_ADS1115 ads;
float Sensor1ReadFunc()
{
    float adc = ads.readADC_SingleEnded(0);
    adc = constrain(adc, 8400, 23000); // Keep the ranges!
    adc = map(adc, 8400, 23000, 100, 0);
    return adc;
}
float Sensor2ReadFunc()
{
    float adc = ads.readADC_SingleEnded(1);
    adc = constrain(adc, 8400, 23000); // Keep the ranges!
    adc = map(adc, 8400, 23000, 100, 0);
    return adc;
}
bool initPumpFunc()
{
    pinMode(14, OUTPUT);
    return true;
}
bool startPumpFunc(int speed)
{
    digitalWrite(14, HIGH);
    return true;
}
bool stopPumpFunc()
{
    digitalWrite(14, LOW);
    return true;
}
bool changePumpSpeedFunc(int speed)
{
    return true;
}
bool lightOnFunc()
{
    digitalWrite(12, HIGH);
    return true;
}
bool lightOffFunc()
{
    digitalWrite(12, LOW);
    return true;
}
bool lightInitFunc()
{
    pinMode(12, OUTPUT);
    return true;
}
#endif