
//https://www.drdobbs.com/cpp/state-patterns-c/184404132?pgno=1
#ifndef WateringMachine_h
#include "state-pattern/WateringMachineStateBase.h"
#include "Light.h"
#include "MoistureSensor.h"
#include "SimplePump.h"

#define WateringMachine_h

class IdleState;

class WateringMachine
{
public:
    WateringMachineStateBase state;
    Light light;
    MoistureSensor moistureSensor1;
    MoistureSensor moistureSensor2;
    SimplePump pump;

public:
    WateringMachine(Light &l, SimplePump &sp, MoistureSensor &ms, MoistureSensor &ms2) : light(l), pump(sp), moistureSensor1(ms), moistureSensor2(ms2)
    {
    }
    void lightsOn(){
         this->state.handleLighting();
    }
    WateringMachine* setState(WateringMachineStateBase const &wmsb)
    {
        this->state = wmsb;
        return this;
    }
    void init(){
        this->state.init();
    }
    void tick(){
        this->state.tick();
    }
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