#include "SwitchStateMachine.h"

SwitchStates SwitchStateMachine::nextState(SwitchCommand command)
{
    switch (command)
    {
    case SwitchCommand::COMMAND_ON:
        if (this->state == SwitchStates::SWITCH_OFF)
        {
            this->state = SwitchStates::SWITCH_ON;
        }
        break;
    case SwitchCommand::COMMAND_OFF:
        if (this->state == SwitchStates::SWITCH_ON)
        {
            this->state = SwitchStates::SWITCH_OFF;
        }
        break;

    default:
        break;
    }
    return this->state;
}