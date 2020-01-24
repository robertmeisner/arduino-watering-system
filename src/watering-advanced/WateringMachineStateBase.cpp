#include "WateringMachineStateBase.h"
WateringMachineStateBase::WateringMachineStateBase(WateringMachine &wm) : context(wm)
{
}
bool WateringMachineStateBase::handleWatering(){};
bool WateringMachineStateBase::handleLighting(){};
bool WateringMachineStateBase::handleMoistureReading(){};
bool WateringMachineStateBase::init(){};
bool WateringMachineStateBase::tick(){};
bool WateringMachineStateBase::setContext(){};