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
    int state = PumpStates::STATE_OFF;
     ~PumpStateMachine() {} // Destructor
     bool start(int speed) {};
     bool changeSpeed(int speed) {};
     bool stop()  {};

protected:
     int nextState(int command); // Needs to be implemented by each subclass
};
