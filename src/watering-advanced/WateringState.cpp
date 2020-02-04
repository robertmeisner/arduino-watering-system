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
            this->context->setState(StateType::LIGHTING_STATE);
            return true;
        }
    }
    return false;
};
bool WateringState::handleWatering() {
    //do nothing?
    cLog("Watering can't be handled when watering",DebugLevel::WARNING);
}
bool WateringState::handleMoistureReading() {
    //read avg for all sensors
    int sensorsAvg=this->context->readSensors();
}
bool IdleState::handleIdle() {}
bool WateringState::init() {}
bool WateringState::tick() {
    // if last time checked is 2 min ago or more 
    // read moisture 
    this->handleMoistureReading();
    //if avg moisture is higher than XXX stop Watering
    this
}
bool WateringState::setContext() {}