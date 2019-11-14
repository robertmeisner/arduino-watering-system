/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "MoistureSensor.h"

MoistureSensor::MoistureSensor(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

int MoistureSensor::read()
{
  //digitalWrite(_pin, HIGH);
  //delay(250);
  //digitalWrite(_pin, LOW);
  //delay(250);
  //digitalWrite(_pin, HIGH); //zasilanie
  //delay(1000);
  this->_moistureReadingNumber++;

  int value = analogRead(this->_pin); // Read analog value
  value = constrain(value, 400, 1023);    // Keep the ranges!
  value = map(value, 400, 1023, 100, 0);
  this->_moistureReadings[_moistureReadingNumber - 1] = value;

  if (_moistureReadingNumber > 7)
  {
    _moistureReadingNumber = 0;
  }
  digitalWrite(3, LOW);
}

int MoistureSensor::readAvg()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}