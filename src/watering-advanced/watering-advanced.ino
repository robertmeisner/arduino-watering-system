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

#include "CommandLine.h"

//#define WATERING_TEST 1

#ifdef WATERING_TEST
#include "ArduinoFunctions.Test.h"
#else
#include "ArduinoFunctions.h"
#endif

//MechanicalButton *mb = new MechanicalButton(12);
//ALWAYS USE h and cpp files!!!!! laways h only declrations and cpp for definiton
//always use ifnotdef def
// calling global variables in global scope is not permitted oO //cry
//https://community.blynk.cc/t/error-isr-not-in-iram/37426/16
//ICACHE_RAM_ATTR void mbInterruptHandler(void)
//{
// xc->handleInterrupt();
//}

WateringMachineConfig config;
WateringMachine *wateringMachine;
static SimplePump pump(startPumpFunc, stopPumpFunc, changePumpSpeedFunc, initPumpFunc, 0); //static so they wont be deleted after setup is detroyed
static Light light(lightOnFunc, lightOffFunc, lightInitFunc);

bool serialCommand(char *commandLine)
{
    //  print2("\nCommand: ", commandLine);
    int result;

    char *ptrToCommandName = strtok(commandLine, delimiters);
    //  print2("commandName= ", ptrToCommandName);

    if (strcmp(ptrToCommandName, "turnLight") == 0)
    { //Modify here
        wateringMachine->turnLightingOn();
    }
    else if (strcmp(ptrToCommandName, "turnIdle") == 0)
    { //Modify here
        wateringMachine->turnIdle();
    }
    else
    {
        nullCommand(ptrToCommandName);
    }
}
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
    // 600000 ms=10 min
    // 14400000 ms = 4 h
    //28800000 ms= 8h
    //57600000 ms =16h
    //char json[] =
    //    "{\"sensor\":\"gps\",\"LIGHTING_INTERVAL\":57600000,\"LIGHTING_DURATION\":28800000,\"WATERING_MAX_DURATION\":600000,\"MOISTURE_TRESHOLD\":34,\"data\":[48.756080,2.302038]}";
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
    //loadWateringConfig(json, config);
    //tak sie tworzy obiekty bez parametrow?!?!?!?!
    unsigned long ONE_HOUR = 1000 * 60 * 60;
    config.LIGHTING_DURATION = ONE_HOUR * 8;
    config.LIGHTING_INTERVAL = ONE_HOUR * 16;
    config.WATERING_MAX_DURATION = ONE_HOUR / 6;
    config.WATERING_MAX_INTERVAL = ONE_HOUR * 24 * 10;
    config.WATERING_MIN_INTERVAL = ONE_HOUR;

    /**
     * 
     * ANALOG
     */
    ads.setGain(GAIN_ONE);
    ads.begin();
    delay(100);

    static std::vector<MoistureSensor> sensors;
    sensors.push_back(MoistureSensor(Sensor1ReadFunc)); //strange object creation
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
    //light.turnOn();
    //delay(2000);
    //light.turnOff();
    bool received = getCommandLineFromSerialPort(CommandLine); //global CommandLine is defined in CommandLine.h
    if (received)
        serialCommand(CommandLine);

    wateringMachine->tick();
    delay(5000);
    // light.
};
