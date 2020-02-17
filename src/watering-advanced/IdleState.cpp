#include "IdleState.h"
#include "WateringMachine.h"
#include "WateringMachineConfig.h"
#include "CustomLog.h"
#include "Light.h"
#include "StateFactory.h"
const char *IdleState::getName()
{
    return "IdleState";
}
bool IdleState::handleWatering() {
    cLog("Changing state from IdleState to WateringState");
    this->context->setState(StateType::WATERING_STATE);
}
bool IdleState::handleLighting() {
     cLog("Changing state from IdleState to LightingState");
    this->context->setState(StateType::LIGHTING_STATE);
}

bool IdleState::handleIdle() {cLog("Idle can't be changed to Idle", DebugLevel::WARNING);}
bool IdleState::init() {
    cLog("Initiating Idle State");
}
bool IdleState::tick()
{
    int sensorsAvg = this->context->getMoistureAvg();
    //if avg moisture is higher than XXX stop Watering

    
    String json= "JSON = ";
    //serializeJson(this->context->config, json);
//cLog(json);
    
    if (sensorsAvg < this->context->config.MOISTURE_TRESHOLD)
    {
        cLog("Moisture under MOISTURE_TRESHOLD");
        this->handleWatering();
    }
    if (this->context->light.getDurationSinceLastChange() > this->context->config.LIGHTING_INTERVAL)
    {
        cLog("Turning on the light");
        this->handleLighting();
    }
    
}