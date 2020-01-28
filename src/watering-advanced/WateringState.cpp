#include "WateringState.h"
#include "WateringMachine.h"
#include "SimplePump.h"
#include "Light.h"
#include "CustomLog.h"
char* WateringState::getName(){
    return "WateringState";
}
bool WateringState::handleLighting()
{
    if (this->context->pump.stop())
    {
        if (this->context->light.turnOn())
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