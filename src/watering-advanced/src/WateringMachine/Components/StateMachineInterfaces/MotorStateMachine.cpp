#include "MotorStateMachine.h"
int MotorStateMachine::nextState(int command)
{
    switch (this->state)
    {
    case MotorStates::STATE_ON:
        if (command == PumpCommand::COMMAND_STOP)
        {
            this->state = MotorStates::STATE_OFF;
        };
        break;
    case MotorStates::STATE_OFF:
        if (command == PumpCommand::COMMAND_START)
        {
            this->state = MotorStates::STATE_ON;
        };
        break;

    default:
    
        break;
    }
    return this->state;
}