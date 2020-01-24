#include "WateringMachine.h"
#include "WateringMachineStateBase.h"
WateringMachine::WateringMachine(Light &l, SimplePump &sp, MoistureSensor &ms, MoistureSensor &ms2) : light(l), pump(sp), moistureSensor1(ms), moistureSensor2(ms2)
{
}
void WateringMachine::lightsOn()
{
    this->state->handleLighting();
}
WateringMachine* WateringMachine::setState(WateringMachineStateBase *wmsb)
{
    this->state = wmsb;
    return this;
}
void WateringMachine::init()
{
    this->state->init();
}
void WateringMachine::tick()
{
    this->state->tick();
}
