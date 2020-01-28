#ifndef WATERING_STATE_H
#define WATERING_STATE_H
#include "WateringMachineStateBase.h"

//#include "../WateringMachine.h"
class WateringState : public WateringMachineStateBase
{
public:
   // WateringState(WateringMachine wm) : context(wm) {}
   using WateringMachineStateBase::WateringMachineStateBase;
    char* getName();
    bool handleWatering() ;
    bool handleLighting() ;
    bool handleMoistureReading() ;
    bool init() ;
    bool tick() ;
    bool setContext() ;
protected:
};
#endif;