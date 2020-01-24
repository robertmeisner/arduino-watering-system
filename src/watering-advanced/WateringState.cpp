#include "WateringState.h"
#include "WateringMachine.h"
#include "SimplePump.h"
#include "Light.h"
bool WateringState::handleLighting()
{
    if (this->context.pump.stop())
    {
        if (this->context.light.turnOn())
        {
            //this->context.setState(LightingState(this->context));
            return true;
        }
    }
    return false;
};
bool WateringState::handleWatering() {}
bool WateringState::handleMoistureReading() {}
bool WateringState::init() {}
bool WateringState::tick() {}
bool WateringState::setContext() {}