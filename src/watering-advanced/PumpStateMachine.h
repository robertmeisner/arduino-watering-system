#include "StateMachine.h"
enum PumpStates
{
    STATE_OFF,
    STATE_ON
};
enum PumpCommand
{
    COMMAND_START,
    COMMAND_STOP

};
class PumpStateMachine : public StateMachine
{
public:
    PumpStates state = PumpStates::STATE_OFF;
    virtual ~PumpStateMachine() {} // Destructor
    virtual bool start(int speed) = 0;
    virtual bool changeSpeed(int speed) = 0;
    virtual bool stop() = 0;

private:
    virtual PumpStates nextState(PumpCommand command) = 0; // Needs to be implemented by each subclass
};
