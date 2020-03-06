#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#ifndef ArduinoFunctions_h
#define ArduinoFunctions_h
static Adafruit_ADS1115 ads;
float Sensor1ReadFunc()
{
    float adc = ads.readADC_SingleEnded(0);
    Serial.println("raw sensor value: " + String(adc));
    adc = constrain(adc, 8400, 23000); // Keep the ranges!
    adc = map(adc, 8400, 23000, 100, 0);
    return adc;
}
float Sensor2ReadFunc()
{
    float adc = ads.readADC_SingleEnded(1);
    Serial.println("raw sensor value: " + String(adc));
    adc = constrain(adc, 8400, 23000); // Keep the ranges!
    adc = map(adc, 8400, 23000, 100, 0);
    return adc;
}

bool startPumpFunc(int speed)
{
    digitalWrite(14, LOW);
    return true;
}
bool stopPumpFunc()
{
    digitalWrite(14, HIGH);
    return true;
}
bool initPumpFunc()
{
    pinMode(14, OUTPUT);
    stopPumpFunc();
    return true;
}
bool changePumpSpeedFunc(int speed)
{
    return true;
}
bool lightOnFunc()
{
    digitalWrite(13, LOW);
    return true;
}
bool lightOffFunc()
{
    digitalWrite(13, HIGH);
    return true;
}
bool lightInitFunc()
{
    pinMode(13, OUTPUT);
    lightOffFunc();
    return true;
}
#endif