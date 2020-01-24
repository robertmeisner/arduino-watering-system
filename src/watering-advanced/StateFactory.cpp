#include "StateFactory.h"
#include "LightingState.h"
#include "WateringState.h"
#include "IdleState.h"
class WateringMachine;
WateringMachineStateBase *StateFactory::getState(StateType type, WateringMachine &m)
{
    switch (type)
    {
    case StateType::WATERING_STATE:
    {
        WateringMachineStateBase *b=new LightingState(m);
        return b;
        break;
}
    case StateType::LIGHTING_STATE:
        /* code */
        break;

    case StateType::IDLE_STATE:
        /* code */
        break;

    default:
        break;
    }
}