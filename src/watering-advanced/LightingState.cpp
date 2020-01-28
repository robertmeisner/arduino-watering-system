#include "LightingState.h"
#include "WateringMachine.h"
#include "Light.h"
#include "SimplePump.h"
#include "CustomLog.h"
#include "StateFactory.h"
//LightingState::LightingState(WateringMachine* wm): WateringMachineStateBase(wm){}
char *LightingState::getName()
{
    return "LightingState";
}
bool LightingState::handleWatering()
{
    cLog("Watering handled by");
    cLog(this->getName());
    this->context->light.turnOff();

    if (!this->context->light.isOn())
    {
        if (this->context->pump.start())
        {
            this->context->setState(StateType::WATERING_STATE);
            return true;
        }
    }
    return false;
}
bool LightingState::handleLighting()
{
    cLog("Lighting handled by");
    cLog(this->getName());
    return false;
}
bool LightingState::handleMoistureReading(){};
bool LightingState::init(){
    this->context->light.turnOn();
};
bool LightingState::tick(){};
bool LightingState::setContext(){};