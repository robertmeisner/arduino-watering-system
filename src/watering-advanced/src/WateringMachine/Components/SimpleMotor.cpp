#include "SimpleMotor.h"
#include <Arduino.h>
#include "../Utils/CustomLog.h"
// IMPLEMENTATION
bool SimpleMotorInitMockFunc()
{
    return true;
}
SimpleMotor::SimpleMotor(bool (*startFunc)(int), bool (*stopFunc)(), bool (*changeSpeedFunc)(int), bool (*initFunc)(), int initialSpeed) : PumpStateMachine()
{
    this->_startFunc = startFunc;
    this->_stopFunc = stopFunc;
    this->_changeSpeedFunc = changeSpeedFunc;
    if (initFunc == nullptr)
    {
        this->_initFunc = SimpleMotorInitMockFunc;
    }
    else
    {
        this->_initFunc = initFunc;
    }
    this->_speed = initialSpeed;
}
bool SimpleMotor::start(int speed)
{
    cLog("Starting the motor");

    this->_startFunc(speed);
    this->nextState(PumpCommand::COMMAND_START);
    this->sinceLastChangeChrono = millis();

    return this->state == PumpStates::STATE_ON;
}

bool SimpleMotor::changeSpeed(int speed)
{
    if (this->state == PumpStates::STATE_OFF)
    {
        if (this->_changeSpeedFunc(speed))
        {
            this->_speed = speed;

            if (this->state == PumpStates::STATE_ON && speed == 0)
            {
                return this->stop();
            }
        }
    }
}
bool SimpleMotor::stop()
{

    if (this->_stopFunc())
    {
        this->sinceLastChangeChrono = millis();
        if (this->nextState(PumpCommand::COMMAND_STOP) == PumpStates::STATE_OFF)
            return true;
    }
    cLog("Couldn't stop the motor");
    return false;
}
unsigned long SimpleMotor::getDurationSinceLastChange()
{
    return millis() - this->sinceLastChangeChrono;
}

bool SimpleMotor::init()
{
    cLog("Initiating SimpleMotor");
    this->_initFunc();
    cLog("Finished initiating of SimpleMotor");
}