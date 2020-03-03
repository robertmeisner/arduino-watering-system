#include "Arduino.h"
#include "SimplePump.h"
#include "Light.h"
#include "MoistureSensor.h"
#include "MechanicalButton.h"
#include "CustomLog.h"
#include "WateringMachine.h"
#include "WateringMachineConfig.h"

#include "WateringMachineStateBase.h"
#include "LightingState.h"
#include "IdleState.h"
#include "WateringState.h"
#include "StateFactory.h"
#include "ArduinoFunctions.h"

//MechanicalButton *mb = new MechanicalButton(12);
//ALWAYS USE h and cpp files!!!!! laways h only declrations and cpp for definiton
//always use ifnotdef def
// calling global variables in global scope is not permitted oO //cry
//https://community.blynk.cc/t/error-isr-not-in-iram/37426/16
//ICACHE_RAM_ATTR void mbInterruptHandler(void)
//{
// xc->handleInterrupt();
//}
#define WATERING_TEST
WateringMachineConfig config;
WateringMachine *wateringMachine;

void setup()
{
    // initialize the serial communication:
    Serial.begin(115200);
    cLog("Setting up the Watering Machine");
    // StaticJsonDocument<500> doc;
    /*
      #define LIGHT_DURATION 3600000  //1h in ms
      #define LIGHT_INTERVAL 86400000 //24h in ms
#define WATERING_CYCLE_DURATION 10000
#define WATERING_CYCLES 250
#define WATERING_CYCLE_PAUSE_DURATION 5000
#define WATERING_MOISTURE_CRITICAL 45
      */
    char json[] =
        "{\"sensor\":\"gps\",\"LIGHTING_INTERVAL\":7200,\"LIGHTING_DURATION\":3600,\"WATERING_MAX_DURATION\":1000,\"MOISTURE_TRESHOLD\":34,\"data\":[48.756080,2.302038]}";
    //cLog("Deserializing Config");
    //cLog(json);
    // Deserialize the JSON document
    //DeserializationError error = deserializeJson(doc, json);

    // Test if parsing succeeds.
    /*if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    }*/
    loadWateringConfig(json, config);
    //tak sie tworzy obiekty bez parametrow?!?!?!?!
    static SimplePump pump(startPumpFunc, stopPumpFunc, changePumpSpeedFunc, initPumpFunc, 0); //static so they wont be deleted after setup is detroyed

    static Light light(lightOnFunc, lightOffFunc, lightInitFunc);

    /**
     * 
     * ANALOG
     */
    ads.setGain(GAIN_ONE);
    ads.begin();
    delay(100);

    static std::vector<MoistureSensor> sensors;
    sensors.push_back(MoistureSensor(Sensor1ReadFunc));//strange object creation 
    sensors.push_back(MoistureSensor(Sensor2ReadFunc));
    //sensors[0].init();
    //sensors[1].init();
    delay(100);
    //cLog("Sensor:");
    //Serial.println(sensors[0].read());
    //cLog("Sensor:");
    //Serial.println(sensors[1].read());

    //mb->setupInterruptHandler(12, mbInterruptHandler, CHANGE);

    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
    static StateFactory sf;
    wateringMachine = new WateringMachine(config, sf, light, pump, sensors); //how to apss sf by reference when no parameters?
    wateringMachine->init();
    cLog("Setting up has finished");
};
void loop()
{
    wateringMachine->tick();
};
