
//https://www.drdobbs.com/cpp/state-patterns-c/184404132?pgno=1
#ifndef WateringMachine_h
//#include "state-pattern/WateringMachineStateBase.h"
#include<vector>
#define WateringMachine_h
#include "StateTypeEnum.h"
#include "ArduinoJson.h"
class WateringMachineStateBase;
class Light;
class MoistureSensor;
class SimplePump;
class StateFactory;
//class StaticJsonDocument;


class WateringMachine
{
public:
    WateringMachine( JsonDocument& _doc,StateFactory &sf,Light &l, SimplePump &sp,  std::vector<MoistureSensor> &moistureSensors);
   void lightsOn();
    void init();
    void tick();
    int getMoistureAvg();
    WateringMachine *setState( StateType type);
    WateringMachineStateBase *state;
    JsonDocument &config;
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