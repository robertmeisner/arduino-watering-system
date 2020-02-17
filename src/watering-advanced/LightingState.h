#ifndef LIGHTING_STATE_H
#define LIGHTING_STATE_H
#include "WateringMachineStateBase.h"
class WateringMachine;
class LightingState : public WateringMachineStateBase
{
public:
    using WateringMachineStateBase::WateringMachineStateBase;
    const char *getName();
    bool handleWatering();
    bool handleLighting();
    bool handleIdle();
    bool init();
    bool tick();
    //LightingState(WateringMachine* wm);

protected:
};

#endif