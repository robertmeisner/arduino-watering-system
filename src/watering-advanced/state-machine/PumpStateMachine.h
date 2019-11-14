#include "StateMachine.h"
class PumpStateMachine : public StateMachine
{
public:
    virtual void drawScreen() = 0; // Needs to be implemented by each subclass

    virtual ~PumpStateMachine() {} // Destructor
private:
    virtual void nextState() = 0;
};
