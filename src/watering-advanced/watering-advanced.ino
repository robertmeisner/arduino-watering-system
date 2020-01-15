#include "SimplePump.h"
#include "Light.h"
#include "MoistureSensor.h"
#include "WateringMachine.h"
#include "state-pattern/IdleState.h"
SimplePump pump(12, 0);
Light light(12);
MoistureSensor moistureSensor1(12);
MoistureSensor moistureSensor2(12);
WateringMachine wateringMachine(light, pump, moistureSensor1, moistureSensor2);

void setup()
{
    Serial.begin(9600); 
    wateringMachine.setState(*new IdleState(wateringMachine)); //rewrite
    wateringMachine.init();
}
void loop()
{
    wateringMachine.tick();
}
