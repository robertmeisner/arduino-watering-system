#ifndef LIGHTING_STATE_H
#define LIGHTING_STATE_H
#include "WateringMachineStateBase.h"
class WateringMachine;
class LightingState : public WateringMachineStateBase
{
public:
    LightingState(WateringMachine& wm);
    bool handleWatering();
    bool handleLighting();
    bool handleMoistureReading();
    bool init();
    bool tick();
    bool setContext();

protected:
};

#endif