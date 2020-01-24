#ifndef STATE_FACTORY_H
#define STATE_FACTORY_H
#include "StateTypeEnum.h"
class WateringMachineStateBase;
class WateringMachine;
class StateFactory
{
public:
    WateringMachineStateBase* getState(StateType type,WateringMachine &m);
};

#endif
