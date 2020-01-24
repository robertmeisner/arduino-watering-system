#include "Arduino.h"
#include "SimplePump.h"
#include "Light.h"
#include "MoistureSensor.h"

#include "WateringMachine.h"

#include "WateringMachineStateBase.h";
#include "LightingState.h"
#include "IdleState.h"
#include "WateringState.h"



#include "StateFactory.h"

SimplePump pump(12, 0);
Light light(12);
MoistureSensor moistureSensor1(12);
MoistureSensor moistureSensor2(12);
WateringMachine wateringMachine(light, pump, moistureSensor1, moistureSensor2);

void setup()
{
    Serial.begin(9600); 
    StateFactory *sf=new StateFactory();
    wateringMachine.setState(sf->getState(StateType::IDLE_STATE,wateringMachine) ); //rewrite
    wateringMachine.init();
};
void loop()
{
    wateringMachine.tick();
};
