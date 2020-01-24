#include "LightingState.h"
#include "WateringMachine.h"
#include "Light.h"
#include "SimplePump.h"
LightingState::LightingState(WateringMachine& wm): WateringMachineStateBase(wm){

}
bool LightingState::handleWatering()
{

    this->context.light.turnOff();

    if (!this->context.light.isOn())
    {
        if (this->context.pump.start())
        {
            // this->context.setState(WateringState(this->context));
            return true;
        }
    }
    return false;
}
bool LightingState::handleLighting()
{
    return false;
}
bool LightingState::handleMoistureReading(){};
bool LightingState::init(){};
bool LightingState::tick(){};
bool LightingState::setContext(){};