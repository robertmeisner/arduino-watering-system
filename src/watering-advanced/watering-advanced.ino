#include "Arduino.h"
#include "ArduinoJson.h"
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
//https://community.blynk.cc/t/error-isr-not-in-iram/37426/16
ICACHE_RAM_ATTR void mbInterruptHandler(void)
{
    // xc->handleInterrupt();
}

WateringMachine *wateringMachine;

void setup()
{
    StaticJsonDocument<500> doc;
    /*
      #define LIGHT_DURATION 3600000  //1h in ms
      #define LIGHT_INTERVAL 86400000 //24h in ms
#define WATERING_CYCLE_DURATION 10000
#define WATERING_CYCLES 250
#define WATERING_CYCLE_PAUSE_DURATION 5000
#define WATERING_MOISTURE_CRITICAL 45
      */
    char json[] =
        "{\"sensor\":\"gps\",\"LIGHTING_INTERVAL\":86400000-3600000,\"LIGHTING_DURATION\":3600000,\"WATERING_MAX_DURATION\":1000,\"MOISTURE_TRESHOLD\":34,\"data\":[48.756080,2.302038]}";
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, json);

    // Test if parsing succeeds.
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    }
    const char *sensor = doc["sensor"];
    long time = doc["time"];
    double latitude = doc["data"][0];
    double longitude = doc["data"][1];

    Serial.begin(74880);
    StateFactory sf; //tak sie tworzy obiekty bez parametrow?!?!?!?!
    SimplePump pump(12, 0);
    Light light(12);
    std::vector<MoistureSensor> sensors;
    sensors.push_back(MoistureSensor(12));
    sensors.push_back(MoistureSensor(12));
    mb->setupInterruptHandler(12, mbInterruptHandler, CHANGE);

    wateringMachine = new WateringMachine(doc, sf, light, pump, sensors);

    wateringMachine->init();
};
void loop()
{
    wateringMachine->tick();
};
