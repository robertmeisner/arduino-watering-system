#ifndef IDLE_STATE_H
#define IDLE_STATE_H
#include "WateringMachineStateBase.h"
//#include "../WateringMachine.h"
class IdleState : public WateringMachineStateBase
{
public:
    //IdleState(WateringMachine wm) : context(wm) {}
    using WateringMachineStateBase::WateringMachineStateBase;
    const char *getName();
    bool handleWatering();
    bool handleLighting();
    bool handleIdle();
    bool init();
    bool tick();

protected:
    //WateringMachine context;
};
#endif