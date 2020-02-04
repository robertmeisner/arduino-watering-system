#ifndef IDLE_STATE_H
#define IDLE_STATE_H
#include "WateringMachineStateBase.h"
//#include "../WateringMachine.h"
class IdleState : public WateringMachineStateBase
{
public:
    //IdleState(WateringMachine wm) : context(wm) {}
    using WateringMachineStateBase::WateringMachineStateBase;
    char *getName();
    bool handleWatering();
    bool handleLighting();
    bool handleMoistureReading();
    bool handleIdle();
    bool init();
    bool tick();
    bool setContext();

protected:
    //WateringMachine context;
};
#endif