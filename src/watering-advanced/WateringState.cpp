#include "WateringState.h"
#include "WateringMachine.h"
#include "SimplePump.h"
#include "Light.h"
#include "CustomLog.h"
char *WateringState::getName()
{
    return "WateringState";
}
bool WateringState::handleLighting()
{
    if (this->context->pump.stop())
    {
        if (this->context->light.turnOn())
        {
            cLog("Changing state from WateringState to LightingState");
            this->context->setState(StateType::LIGHTING_STATE);
            return true;
        }
    }
    return false;
};
bool WateringState::handleWatering()
{
    //do nothing?
    cLog("Watering can't be handled when watering", DebugLevel::WARNING);
}

bool WateringState::handleIdle()
{

    if (this->context->light.turnOff())
    {
        cLog("Changing state from WateringState to IdleState");
        this->context->setState(StateType::IDLE_STATE);
        return true;
    }
}
bool WateringState::init()
{
    cLog("Initiating the WateringState");
    if (this->context->pump.start())
    {
       cLog("Couldn't start the pump.");
        this->handleIdle();
    }
    cLog("Initiating of the WateringState has finished");
}
bool WateringState::tick()
{
    cLog("Watering State tick started", DebugLevel::DEBUG);
    // if last time checked is 2 min ago or more
    // read moisture

    int sensorsAvg = this->context->getMoistureAvg();
    //if avg moisture is higher than XXX stop Watering
    if (sensorsAvg > this->context->config['MOISTURE_TRESHOLD'])
    {
        cLog(String("Moisture sensor is over MOISTURE_TRESHOLD: ") + String(sensorsAvg) +">" , DebugLevel::DEBUG);
        //cLog( (this->context->config['MOISTURE_TRESHOLD']);
        cLog("Stopping Watering");
        //    this->handleIdle();
    }
    cLog(String("Moisture sensor is below MOISTURE_TRESHOLD: ") + sensorsAvg + String("<") + this->context->config['MOISTURE_TRESHOLD'], DebugLevel::DEBUG);
    cLog("Watering State tick finished", DebugLevel::DEBUG);
}
