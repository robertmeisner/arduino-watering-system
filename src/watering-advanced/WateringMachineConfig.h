#ifndef WATERING_MACHINE_CONFIG_H
#define WATERING_MACHINE_CONFIG_H
/**
 * 
 *   #define LIGHT_DURATION 3600000  //1h in ms
      #define LIGHT_INTERVAL 86400000 //24h in ms
#define WATERING_CYCLE_DURATION 10000
#define WATERING_CYCLES 250
#define WATERING_CYCLE_PAUSE_DURATION 5000
#define WATERING_MOISTURE_CRITICAL 45
char json[] =
        "{\"sensor\":\"gps\",\"LIGHTING_INTERVAL\":82800000,\"LIGHTING_DURATION\":3600000,\"WATERING_MAX_DURATION\":1000,\"MOISTURE_TRESHOLD\":34,\"data\":[48.756080,2.302038]}";
 * */
struct WateringMachineConfig
{
  int LIGHTING_INTERVAL;
  int LIGHTING_DURATION;
  int WATERING_MAX_DURATION;
  int MOISTURE_TRESHOLD;
  char nodeRedHostname[128];
  char nodeRedUser[64];
  char nodeRePass[64];
  int nodeRedPort;
};
void loadWateringConfig(const char *file, WateringMachineConfig &config);
#endif