#include "SimplePump.h"
#include "Arduino.h"
// IMPLEMENTATION

SimplePump::SimplePump(int pin, int initialSpeed)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
    this->start(initialSpeed);
}
bool SimplePump::start(int speed)
{
    digitalWrite(this->_pin, LOW);
    this->nextState(PumpCommand::COMMAND_START);
    return this->state == PumpStates::STATE_ON;
}

bool SimplePump::changeSpeed(int speed)
{
    this->speed = speed;
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
    this->nextState(PumpCommand::COMMAND_STOP);
    return true;
}
int SimplePump::getTimeRunning()
{
    return 0;
}
PumpStates SimplePump::nextState(PumpCommand command)
{
    switch (this->state)
    {
    case PumpStates::STATE_ON:
        if (command == PumpCommand::COMMAND_STOP)
        {
            this->state = PumpStates::STATE_OFF;
        };
        break;
    case PumpStates::STATE_OFF:
        if (command == PumpCommand::COMMAND_START)
        {
            this->state = PumpStates::STATE_ON;
        };
        break;

    default:
        break;
    }
    return this->state;
}