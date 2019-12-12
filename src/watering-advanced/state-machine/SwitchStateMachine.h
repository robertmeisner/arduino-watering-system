#include "StateMachine.h"
enum SwitchStates
{
  STATE_OFF,
  STATE_ON
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
  SwitchStates state = SwitchStates::STATE_OFF;
  virtual bool turnOn() = 0;
  virtual bool turnOff() = 0;
  virtual ~SwitchStateMachine() {} // Destructor
protected:
  SwitchStates nextState(SwitchCommand command)
  {
    switch (command)
    {
    case SwitchCommand::COMMAND_ON:
      if (this->state == SwitchStates::STATE_OFF)
      {
        this->state = SwitchStates::STATE_ON;
      }
      break;
    case SwitchCommand::COMMAND_OFF:
      if (this->state == SwitchStates::STATE_ON)
      {
        this->state = SwitchStates::STATE_OFF;
      }
      break;

    default:
      break;
    }
    return this->state;
  }
};
