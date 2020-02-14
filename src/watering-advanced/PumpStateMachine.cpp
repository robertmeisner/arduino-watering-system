#include "PumpStateMachine.h"
PumpStates PumpStateMachine::nextState(PumpCommand command)
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