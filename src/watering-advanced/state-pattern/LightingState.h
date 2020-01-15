#ifndef LIGHTING_STATE_H
#define LIGHTING_STATE_H
#include "WateringMachineStateBase.h"
#include "WateringState.h"
#include "../WateringMachine.h"
class LightingState : public WateringMachineStateBase
{
public:
    LightingState(WateringMachine wm) : context(wm) {}
    bool handleWatering() {}
    bool handleLighting() {}
    bool handleMoistureReading() {}
    bool init() {}
    bool tick() {}
    bool setContext() {}
protected:
    WateringMachine context;
};
bool LightingState::handleWatering()
{

    this->context.light.turnOff();

    if (!this->context.light.isOn())
    {
        if (this->context.pump.start())
        {
            this->context.setState(WateringState(this->context));
            return true;
        }
    }
    return false;
}
bool LightingState::handleLighting()
{
    return false;
}
#endif