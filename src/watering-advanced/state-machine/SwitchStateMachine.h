#include "StateMachine.h"
#ifndef SWITCH_STATE_MACHINE_H
#define SWITCH_STATE_MACHINE_H
enum SwitchStates
{
  SWITCH_OFF,
  SWITCH_ON
};
enum SwitchCommand
{
  COMMAND_ON,
  COMMAND_OFF
};
class SwitchStateMachine : public StateMachine
{
public:
  SwitchStateMachine() {}
  SwitchStates state = SwitchStates::SWITCH_OFF;
  virtual bool turnOn() = 0;
  virtual bool turnOff() = 0;
  virtual ~SwitchStateMachine() {} // Destructor
protected:
  SwitchStates nextState(SwitchCommand command)
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
};
#endif