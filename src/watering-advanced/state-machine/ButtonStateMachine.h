#include "StateMachine.h"
enum class ButtonModes
{
    MODE_PULLUP,
    MODE_PULLDOWN
};
enum class ButtonStates
{
    STATE_OPEN,
    STATE_RISING,
    STATE_CLOSED,
    STATE_IS_FALLING
};
enum class ButtonCommand
{
    COMMAND_PRESSED,
    COMMAND_RELEASED
};
class ButtonStateMachine : public StateMachine
{
public:
    ButtonStates state = ButtonStates::STATE_OPEN;
   
    ButtonStates getState()
    {
        return this->state;
    }
    bool isPressed()
    {
        if (this->state == ButtonStates::STATE_IS_FALLING && this->state == ButtonStates::STATE_CLOSED)
            return true;
        return false;
    }
    virtual ~ButtonStateMachine() {} // Destructor
private:
    virtual bool nextState() = 0;
};
