#include "StateFactory.h"
#include "LightingState.h"
#include "WateringState.h"
#include "IdleState.h"
class WateringMachine;
StateFactory::StateFactory(){}
WateringMachineStateBase* StateFactory::getState(StateType type, WateringMachine *m)
{

    switch (type)
    {
    case StateType::WATERING_STATE:
    {
        WateringMachineStateBase* l= new WateringState(m);
        return l;
        break;
}
    case StateType::LIGHTING_STATE:
        WateringMachineStateBase* l= new LightingState(m);
        return l;
        break;

    case StateType::IDLE_STATE:
        WateringMachineStateBase* l= new IdleState(m);
        return l;
        break;

    default:
        break;
    }
}