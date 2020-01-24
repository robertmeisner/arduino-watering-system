#ifndef IDLE_STATE_H
#define IDLE_STATE_H
#include "WateringMachineStateBase.h"
//#include "../WateringMachine.h"
class IdleState : public WateringMachineStateBase
{
public:
   //IdleState(WateringMachine wm) : context(wm) {}
    bool handleWatering() ;
    bool handleLighting() ;
    bool handleMoistureReading() ;
    bool init() ;
    bool tick() ;
    bool setContext() ;

protected:
    //WateringMachine context;
};
#endif