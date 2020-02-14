#include "IdleState.h"
#include "WateringMachine.h"
#include "CustomLog.h"
#include "Light.h"
#include "StateFactory.h"
char *IdleState::getName()
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

bool IdleState::handleIdle() {cLog("Idle can't be handled when idle", DebugLevel::WARNING);}
bool IdleState::init() {}
bool IdleState::tick()
{
    int sensorsAvg = this->context->getMoistureAvg();
    //if avg moisture is higher than XXX stop Watering

    if (sensorsAvg < this->context->config['MOISTURE_TRESHOLD'])
    {
        cLog("Moisture under MOISTURE_TRESHOLD");
        this->handleWatering();
    }
    if (this->context->light.getDurationSinceLastChange() > this->context->config['LIGHT_INTERVAL'])
    {
        cLog("Turning on the light");
        this->handleLighting();
    }
}