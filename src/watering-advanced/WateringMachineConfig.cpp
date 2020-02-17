
#include "WateringMachineConfig.h"
#include "ArduinoJson.h"
void loadWateringConfig(const char *file, WateringMachineConfig &config)
{
  // Open file for reading
  //File file = SD.open(filename);

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Copy values from the JsonDocument to the Config
  config.MOISTURE_TRESHOLD = doc["MOISTURE_TRESHOLD"] | 34;
  config.LIGHTING_INTERVAL = doc["LIGHTING_INTERVAL"] | 82800000;
  config.LIGHTING_DURATION = doc["LIGHTING_DURATION"] | 3600000;
  config.WATERING_MAX_DURATION = doc["WATERING_MAX_DURATION"] | 3600000;
  //strlcpy(config.hostname,                  // <- destination
  //        doc["hostname"] | "example.com",  // <- source
  //        sizeof(config.hostname));         // <- destination's capacity

  // Close the file (Curiously, File's destructor doesn't close the file)
  //file.close();
}