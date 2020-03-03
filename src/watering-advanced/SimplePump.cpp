#include "SimplePump.h"
#include "Arduino.h"
#include "CustomLog.h"
// IMPLEMENTATION
bool SimplePumpInitMockFunc()
{
    return true;
}
SimplePump::SimplePump(bool (*startFunc)(int), bool (*stopFunc)(), bool (*changeSpeedFunc)(int), bool (*initFunc)(), int initialSpeed) : PumpStateMachine()
{
    this->_startFunc = startFunc;
    this->_stopFunc = stopFunc;
    this->_changeSpeedFunc = changeSpeedFunc;
    if (initFunc == nullptr)
    {
        this->_initFunc = SimplePumpInitMockFunc;
    }
    else
    {
        this->_initFunc = initFunc;
    }
    this->_speed = initialSpeed;
}
bool SimplePump::start(int speed)
{
    cLog("Starting the pump");

    this->_startFunc(speed);
    cLog("Starting the pump2");
    this->nextState(PumpCommand::COMMAND_START);
    this->sinceLastChangeChrono = millis();
    cLog("Starting the pump3");
    Serial.println(PumpStates::STATE_ON);
    Serial.println(this->state );
    Serial.println(this->state == PumpStates::STATE_ON);
    return this->state == PumpStates::STATE_ON;
}

bool SimplePump::changeSpeed(int speed)
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
bool SimplePump::stop()
{

    if (this->_stopFunc())
    {
        this->sinceLastChangeChrono = millis();
        if (this->nextState(PumpCommand::COMMAND_STOP) == PumpStates::STATE_OFF)
            return true;
    }
    cLog("Couldn't stop the pump");
    return false;
}
unsigned long SimplePump::getDurationSinceLastChange()
{
    return millis() - this->sinceLastChangeChrono;
}

bool SimplePump::init()
{
    cLog("Initiating SimplePump");
    this->_initFunc();
    cLog("Finished initiating of SimplePump");
}