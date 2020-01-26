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

SimplePump pump(12, 0);
Light light(12);
MoistureSensor moistureSensor1(12);
MoistureSensor moistureSensor2(12);

MechanicalButton *mb=new MechanicalButton(12);
// calling global variables in global scope is not permitted oO //cry
void mbInterruptHandler(void)
{
 // xc->handleInterrupt();
}


WateringMachine wateringMachine(light, pump, moistureSensor1, moistureSensor2);

void setup()
{
 
    Serial.begin(9600); 

    mb->setupInterruptHandler(12, mbInterruptHandler,CHANGE);
    StateFactory *sf=new StateFactory();
    wateringMachine.setState(sf->getState(StateType::IDLE_STATE,wateringMachine) ); //rewrite
    wateringMachine.init();
};
void loop()
{
    wateringMachine.tick();
};
