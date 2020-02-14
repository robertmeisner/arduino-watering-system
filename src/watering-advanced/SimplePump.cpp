#include "SimplePump.h"
#include "Arduino.h"
#include "CustomLog.h"
// IMPLEMENTATION

SimplePump::SimplePump(int pin, int initialSpeed)
{
    this->_pin = pin;
    this->_speed = initialSpeed;
}
bool SimplePump::start(int speed)
{
    cLog("Starting the pump");

    digitalWrite(this->_pin, LOW);
    this->nextState(PumpCommand::COMMAND_START);
    this->sinceLastChangeChrono = millis();
    return this->state == PumpStates::STATE_ON;
}

bool SimplePump::changeSpeed(int speed)
{
    this->_speed = speed;
    if (this->state == PumpStates::STATE_ON && speed == 0)
    {
        return this->stop();
    }
    else if (this->state == PumpStates::STATE_OFF && speed > 0)
    {
        return this->start();
    }
}
bool SimplePump::stop()
{
    digitalWrite(this->_pin, HIGH);
    this->sinceLastChangeChrono = millis();
    this->nextState(PumpCommand::COMMAND_STOP);
    return true;
}
unsigned long SimplePump::getDurationSinceLastChange()
{
    return millis() - this->sinceLastChangeChrono;
}

void SimplePump::init()
{
    cLog("Initiating SimplePump");
    pinMode(this->_pin, OUTPUT);
}