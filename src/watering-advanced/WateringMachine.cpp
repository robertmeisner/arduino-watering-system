#include "WateringMachine.h"
#include "WateringMachineConfig.h"
#include "WateringMachineStateBase.h"
#include "CustomLog.h"
#include "Light.h"
#include "MoistureSensor.h"
#include "SimplePump.h"
#include "IdleState.h"
#include "StateFactory.h"

WateringMachine::WateringMachine(WateringMachineConfig &doc, StateFactory &sf, Light &l, SimplePump &sp, std::vector<MoistureSensor> &ms) : config(doc), stateFactory(sf), light(l), pump(sp), moistureSensors(ms)
{
}
void WateringMachine::lightsOn()
{
    this->state->handleLighting();
}
WateringMachine *WateringMachine::setState(StateType type)
{
    cLog("3 Sensors Count:" + String(moistureSensors.size()));
    this->state = this->stateFactory.getState(type, this);
    this->state->init();
    cLog("4 Sensors Count:" + String(moistureSensors.size()));
    return this;
}

int WateringMachine::getMoistureAvg()
{
    cLog("5 Sensors Count:" + String(moistureSensors.size()));
    cLog(String("Trying to obtain Moisture Sensors read outs"));
    if (this->moistureSensors.size() == 0)
    {
        cLog("No Moisture Sensors detected.", DebugLevel::FATAL);
        return 100;
    }

    int avg = 0;
    //for some reason iterator doesnt work??
    //for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    // {
    //    avg += it->readAvg();
    //}

    for (int i = 0; i < this->moistureSensors.size(); i++)
    {
        // avg =avg+ (this->moistureSensors.at(i).readAvg());
    }

    cLog(String("Average for all Moisture sensors reads: ") + (avg / this->moistureSensors.size()));
    return avg / this->moistureSensors.size();
}
bool WateringMachine::init()
{
    cLog("1 Sensors Count:" + String(moistureSensors.size()));
    // inititate the components
    this->light.init();
    for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    {
        it->init();
    }
    this->pump.init();
    cLog("2 Sensors Count:" + String(moistureSensors.size()));
    //set initital state
    this->setState(StateType::IDLE_STATE); //init juz tutaj ma miejsce
    cLog("2a Sensors Count:" + String(moistureSensors.size()));
}
void WateringMachine::tick()
{
    this->state->tick();
}
