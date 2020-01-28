
//https://www.drdobbs.com/cpp/state-patterns-c/184404132?pgno=1
#ifndef WateringMachine_h
//#include "state-pattern/WateringMachineStateBase.h"
#include<vector>
#define WateringMachine_h

class WateringMachineStateBase;
class Light;
class MoistureSensor;
class SimplePump;
class StateFactory;

class WateringMachine
{
public:
    WateringMachine(StateFactory &sf,Light &l, SimplePump &sp,  std::vector<MoistureSensor> &moistureSensors);
   void lightsOn();
    void init();
    void tick();
    WateringMachine *setState( WateringMachineStateBase *wmsb);
    WateringMachineStateBase *state;
    Light &light;
    std::vector<MoistureSensor> &moistureSensors;
    SimplePump &pump;
    StateFactory &stateFactory;
};
#endif
//Humidity sensor #1
//Humidity Sensor #2
//Pumps switch
//Light
//Screen
//Switch
//Button
//Machine