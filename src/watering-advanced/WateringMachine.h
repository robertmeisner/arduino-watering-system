
#ifndef WateringMachine_h
#include "state-pattern/WateringMachineStateBase.h"
#include "Light.h"
#include "MoistureSensor.h"
#include "SimplePump.h"

#define WateringMachine_h

class WateringMachine
{
private:
    WateringMachineStateBase state;
    int lastWateringChrono;
    int lastLightingChrono;
    int lightingInterval;
    int lightingDuration;
    int lastMoistureChrono;
    int avgMoisture;
    Light* light;
    MoistureSensor* moisture[2];
    SimplePump* pump;
    WateringMachine(int lightPin,int moisturePin1,int moisturePin2)
    {
        this->light = new Light(lightPin);
        this->moisture[0]= new MoistureSensor(moisturePin1);
        this->moisture[1]= new MoistureSensor(moisturePin1);
        this-<pump=new SimplePump
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