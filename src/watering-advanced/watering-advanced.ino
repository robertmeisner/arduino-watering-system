#include "Arduino.h"
#include "SimplePump.h"
#include "Light.h"
#include "MoistureSensor.h"
#include "MechanicalButton.h"

#include "WateringMachine.h"

#include "WateringMachineStateBase.h";
#include "LightingState.h"
#include "IdleState.h"
#include "WateringState.h"

#include "StateFactory.h"

MechanicalButton *mb = new MechanicalButton(12);
// calling global variables in global scope is not permitted oO //cry
void mbInterruptHandler(void)
{
    // xc->handleInterrupt();
}

WateringMachine *wateringMachine;

void setup()
{

    Serial.begin(9600);
    StateFactory sf; //tak sie tworzy obiekty bez parametrow?!?!?!?!
    SimplePump pump(12, 0);
    Light light(12);
    std::vector<MoistureSensor> sensors;
    sensors.push_back(MoistureSensor(12));
    sensors.push_back(MoistureSensor(12));
    mb->setupInterruptHandler(12, mbInterruptHandler, CHANGE);

    wateringMachine = new WateringMachine(sf, light, pump, sensors);

    wateringMachine->init();
};
void loop()
{
    wateringMachine->tick();
};
