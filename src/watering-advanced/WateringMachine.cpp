#include "WateringMachine.h"
#include "WateringMachineStateBase.h"
#include "CustomLog.h"
#include "Light.h"
#include "MoistureSensor.h"
#include "SimplePump.h"
#include "IdleState.h"
#include "StateFactory.h"
#include <ArduinoJson.h>

WateringMachine::WateringMachine( JsonDocument& _doc,StateFactory &sf, Light &l, SimplePump &sp, std::vector<MoistureSensor> &ms) : stateFactory(sf), light(l), pump(sp), moistureSensors(ms),config(_doc)
{
    //this->state->setContext(this);
}
void WateringMachine::lightsOn()
{
    this->state->handleLighting();
}
WateringMachine *WateringMachine::setState(StateType type)
{
    
    this->state = this->stateFactory.getState(type, this);
    this->state->init();
    return this;
}

int WateringMachine::getMoistureAvg()
{
    if (this->moistureSensors.size() == 0)
    {
        cLog("No Moisture Sensors detetected.", DebugLevel::FATAL);
        return 100;
    }
    int avg = 0;
    for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    {
        avg += it->readAvg();
    }
    return avg / this->moistureSensors.size();
}
void WateringMachine::init()
{
    // inititate the components
    this->light.init();
    for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    {
        it->init();
    }
    this->pump.init();
    //set initital state
    this->setState(StateType::IDLE_STATE);
}
void WateringMachine::tick()
{
    this->state->tick();
}
