#include "StateMachine.h"
enum MotorStates
{
    STATE_OFF,
    STATE_ON
};
enum PumpCommand
{
    COMMAND_START,
    COMMAND_STOP

};
class MotorStateMachine : public StateMachine
{
public:
    int state = MotorStates::STATE_OFF;
     ~MotorStateMachine() {} // Destructor
     bool start(int speed) {};
     bool changeSpeed(int speed) {};
     bool stop()  {};

protected:
     int nextState(int command); // Needs to be implemented by each subclass
};
