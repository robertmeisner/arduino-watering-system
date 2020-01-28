#include "WateringMachineStateBase.h"
WateringMachineStateBase::WateringMachineStateBase( ) {}
WateringMachineStateBase::WateringMachineStateBase( WateringMachine* wm) : context(wm){}
char* WateringMachineStateBase::getName( ) {}
bool WateringMachineStateBase::handleWatering(){};
bool WateringMachineStateBase::handleLighting(){};
bool WateringMachineStateBase::handleMoistureReading(){};
bool WateringMachineStateBase::init(){};
bool WateringMachineStateBase::tick(){};
bool WateringMachineStateBase::setContext(WateringMachine *cont){
    this->context=cont;
};