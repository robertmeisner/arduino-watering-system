#include "WateringMachine.h"
#include "WateringMachineStateBase.h"
#include "CustomLog.h"
#include "Light.h"
#include "MoistureSensor.h"
#include "SimplePump.h"
#include "IdleState.h"
#include "StateFactory.h"

WateringMachine::WateringMachine(StateFactory &sf, Light &l, SimplePump &sp, std::vector<MoistureSensor> &ms) : stateFactory(sf), light(l), pump(sp), moistureSensors(ms)
{
    this->setState(StateType::IDLE_STATE);
    //this->setState()
    //this->state->setContext(this);
}
void WateringMachine::lightsOn()
{
    this->state->handleLighting();
}
WateringMachine *WateringMachine::setState(StateType type)
{
    this->state = this->stateFactory.getState(type, this);
    return this;
}

int WateringMachine::getMoistureAvg()
{
     for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    {
        it->init();
    }
}
void WateringMachine::init()
{
    this->light.init();
    for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    {
        it->init();
    }
    this->pump.init();
    //remove?
    this->state->init();
}
void WateringMachine::tick()
{
    this->state->tick();
}
