
//https://www.drdobbs.com/cpp/state-patterns-c/184404132?pgno=1
#ifndef WateringMachine_h
//#include "state-pattern/WateringMachineStateBase.h"

#define WateringMachine_h

class WateringMachineStateBase;
class Light;
class MoistureSensor;
class SimplePump;

class WateringMachine
{
public:
    WateringMachine(Light &l, SimplePump &sp, MoistureSensor &ms, MoistureSensor &ms2);
    void lightsOn();
    WateringMachine* setState(WateringMachineStateBase *wmsb);
    void init();
    void tick();
    WateringMachineStateBase *state;
    Light &light;
    MoistureSensor &moistureSensor1;
    MoistureSensor &moistureSensor2;
    SimplePump &pump;
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