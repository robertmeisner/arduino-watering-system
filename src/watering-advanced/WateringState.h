#ifndef WATERING_STATE_H
#define WATERING_STATE_H
#include "WateringMachineStateBase.h"

//#include "../WateringMachine.h"
class WateringState : public WateringMachineStateBase
{
public:
    // WateringState(WateringMachine wm) : context(wm) {}
    using WateringMachineStateBase::WateringMachineStateBase;
    const char *getName();
    bool handleWatering();
    bool handleLighting();
    bool handleMoistureReading();
    bool handleIdle();
    bool init();
    bool tick();

protected:
    int sensorsAverage = 100;
};
#endif