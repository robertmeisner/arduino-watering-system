#ifndef WATERING_STATE_H
#define WATERING_STATE_H
#include "WateringMachineStateBase.h"
#include "LightingState.h"
#include "../WateringMachine.h"
class WateringState : public WateringMachineStateBase
{

public:
    WateringState(WateringMachine wm) : context(wm) {}
    bool handleWatering() {}
    bool handleLighting() {}
    bool handleMoistureReading() {}
    bool init() {}
    bool tick() {}
    bool setContext() {}
protected:
    WateringMachine context;
};
bool WateringState::handleLighting()
{
    if (this->context.pump.stop())
    {
        if (this->context.light.turnOn())
        {
            this->context.setState(LightingState(this->context));
            return true;
        }  
    }
    return false;
};
#endif 