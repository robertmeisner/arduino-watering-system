#include "LightingState.h"
#include "WateringMachine.h"
#include "Light.h"
#include "SimplePump.h"
#include "CustomLog.h"
#include "StateFactory.h"
//LightingState::LightingState(WateringMachine* wm): WateringMachineStateBase(wm){}
const char *LightingState::getName()
{
    return "LightingState";
}
bool LightingState::handleWatering()
{
    this->context->light.turnOff();

    if (!this->context->light.isOn())
    {
        if (this->context->pump.start())
        {
            cLog("Changing state from LightingState to WateringState");
            this->context->setState(StateType::WATERING_STATE);
            return true;
        }
    }
    return false;
}
bool LightingState::handleLighting()
{
    cLog("Lighting can't be handled when lighting", DebugLevel::WARNING);
    return false;
}
bool LightingState::handleIdle()
{
    this->context->light.turnOff();
    if (!this->context->light.isOn())
    {
        cLog("Changing state from LightingState to IdleState");
        this->context->setState(StateType::IDLE_STATE);
        return true;
    }else{
         cLog("Couldn't turn lights off");
    }
    return false;
};
bool LightingState::init()
{
    cLog("Initiating the LightingState");
    this->context->light.turnOn();
};
bool LightingState::tick()
{
    
    if ( this->context->light.getDurationSinceLastChange()>this->context->config.LIGHTING_DURATION)
    {
        cLog( "Switching back to IdleState: "+this->context->light.getDurationSinceLastChange()+'>'+this->context->config.LIGHTING_DURATION);
        return this->handleIdle();
    }
    return true;
};
