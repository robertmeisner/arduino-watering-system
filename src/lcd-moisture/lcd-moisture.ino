
#include <EdgeDebounceLite.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#define VERSION 2.0
// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN 4

SSD1306AsciiAvrI2c oled;
EdgeDebounceLite debounce;
// https://github.com/greiman/SSD1306Ascii

/**
 * Machine states declarations
 */
enum MoistureStates
{
  STATE_READ,
  STATE_IDLE
};
MoistureStates moistureState = MoistureStates::STATE_READ;
enum class SwitchModes
{
  MODE_PULLUP,
  MOD_PULLDOWN
};
SwitchModes switchMode = SwitchModes::MOD_PULLDOWN;
enum class SwitchStates
{
  STATE_OPEN,
  STATE_RISING,
  STATE_CLOSED,
  STATE_IS_FALLING
};
SwitchStates switchState = SwitchStates::STATE_OPEN;
enum class PumpStates
{
  STATE_OFF,
  STATE_ON
};
PumpStates pumpState = PumpStates::STATE_OFF;
enum class WaterLevelStates
{
  STATE_OK,
  STATE_NOT_OK
};
WaterLevelStates waterLevelState = WaterLevelStates::STATE_OK;
enum class WateringMachineStates
{
  STATE_WAIT,
  STATE_CYCLE_ON,
  STATE_CYCLE_PAUSE
};
WateringMachineStates wateringState = WateringMachineStates::STATE_WAIT;
enum class LightStates
{
  STATE_OFF,
  STATE_ON
};
LightStates lightState = LightStates::STATE_ON;
enum class DisplayStates : byte
{
  STATE_OFF,
  STATE_MOISTURE,
  STATE_WATERING,
  STATE_LIGHT,
  STATE_WATER_LEVEL
};
DisplayStates displayState = DisplayStates::STATE_MOISTURE;
/**
 * MOISTURE machine
 */

byte moisturePin[2] = {A1, A2};
byte moistureReadings[2][8] = {
    {100, 100, 100, 100, 100, 100, 100, 100},
    {100, 100, 100, 100, 100, 100, 100, 100}};
byte moistureReadingNumber = 1;
#define MOISTURE_READING_DELAY 120000
unsigned long moistureReadingChrono;

void readMoisture()
{
  digitalWrite(3, HIGH); //zasilanie
  delay(200);
  moistureReadingNumber++;
  for (byte i = 0; i < sizeof(moistureReadings) / sizeof(moistureReadings[0]); i++)
  {

    int value = analogRead(moisturePin[i]); // Read analog value
    value = constrain(value, 400, 1023);    // Keep the ranges!
    value = map(value, 400, 1023, 100, 0);
    moistureReadings[i][moistureReadingNumber - 1] = value;

    if (moistureReadingNumber > sizeof(moistureReadings[0]) - 1)
    {
      moistureReadingNumber = 0;
    }
  }
  digitalWrite(3, LOW);
}
int moistureSensorAvg(int i)
{
  int avg = 0;
  for (byte j = 0; j < sizeof(moistureReadings[i]); j++)
  {
    avg += moistureReadings[i][j];
  }
  return avg / sizeof(moistureReadings[i]);
}
void moistureMachineInit()
{
  pinMode(3, OUTPUT);
}
void moistureMachine()
{
  switch (moistureState)
  {
  case (MoistureStates::STATE_IDLE):
    if (millis() - moistureReadingChrono >= MOISTURE_READING_DELAY)
    {
      //disable electricity
      moistureState = MoistureStates::STATE_READ;
    }
    break;
  case (MoistureStates::STATE_READ):
    readMoisture();
    moistureState = MoistureStates::STATE_IDLE;
    moistureReadingChrono = millis();
    break;
  default:
    break;
  }
}
/**
 * SWITCH MACHINE
 */
byte switchPin = 2;

void switchMachineInit()
{
  pinMode(switchPin, INPUT);
}
void switchMachine()
{
  byte pinIs = debounce.pin(switchPin); //Debounce the pin
  if (switchMode == SwitchModes::MODE_PULLUP)
    pinIs = !pinIs; //Reverse the read if Pullup
  switch (switchState)
  {
  case (SwitchStates::STATE_CLOSED):
    if (pinIs == LOW)                               //If pin is LOW
      switchState = SwitchStates::STATE_IS_FALLING; //Change state to IS_FALLING
    break;
  case (SwitchStates::STATE_IS_FALLING):
    //TODO             //Do something (The switch has been clicked)
    switchState = SwitchStates::STATE_OPEN; //Change state to IS_OPEN (Not falling anymore)
    break;
  case (SwitchStates::STATE_OPEN):
    if (pinIs == HIGH)                          //If pin is HIGH
      switchState = SwitchStates::STATE_RISING; //Change state to IS_RISING
    break;
  case (SwitchStates::STATE_RISING):
    switchState = SwitchStates::STATE_CLOSED; //Change state to IS_CLOSED (Not rising anymore)
    break;

  default:
    break;
  }
}
/**
 * PUMP MACHINE
 */
byte pumpPin = 10;

void pumpOn()
{
  pumpState = PumpStates::STATE_ON;
}
void pumpOff()
{
  pumpState = PumpStates::STATE_OFF;
}
void pumpMachineInit()
{
  pinMode(pumpPin, OUTPUT);
}
void pumpMachine()
{

  switch (pumpState)
  {
  case (PumpStates::STATE_OFF):
    digitalWrite(pumpPin, HIGH);
    if (wateringState == WateringMachineStates::STATE_CYCLE_ON)
    {
      pumpState = PumpStates::STATE_ON;
    }
    break;
  case (PumpStates::STATE_ON):
    digitalWrite(pumpPin, LOW);
    if (wateringState == WateringMachineStates::STATE_CYCLE_PAUSE || wateringState == WateringMachineStates::STATE_WAIT)
    {
      pumpState = PumpStates::STATE_OFF;
    }
    break;
  default:
    break;
  }
}

/**
 * WATER LEVEL MACHINE
 */

bool waterLevelCheck()
{
  return true;
}
void waterLevelMachine()
{

  switch (waterLevelState)
  {
  case (WaterLevelStates::STATE_OK):
    if (!waterLevelCheck())
    {
      waterLevelState = WaterLevelStates::STATE_NOT_OK;
    }
    break;
  case (WaterLevelStates::STATE_NOT_OK):
    if (waterLevelCheck())
    {
      waterLevelState = WaterLevelStates::STATE_OK;
    }
    break;

  default:
    break;
  }
}

/**
 * WATERING MACHINE
 */

#define WATERING_CYCLE_DURATION 5000
#define WATERING_CYCLES 190
#define WATERING_CYCLE_PAUSE_DURATION 6000
#define WATERING_MOISTURE_CRITICAL 40
unsigned int wateringCycleCount = 0;
unsigned long wateringCycleChrono;
unsigned long wateringCyclePauseChrono;

bool wateringNeeded()
{

  bool critical = false;
  for (byte i = 0; i < sizeof(moistureReadings) / sizeof(moistureReadings[0]); i++)
  {
    int avg = moistureSensorAvg(i);
    if (avg < WATERING_MOISTURE_CRITICAL)
    {
      critical = true;
    }
  }
  Serial.println("wateringNeeded");
  Serial.println(critical);
  return critical;
}
void wateringMachineInit()
{
}
void wateringMachine()
{

  switch (wateringState)
  {
  case (WateringMachineStates::STATE_WAIT):
    if (wateringNeeded())
    {
      wateringCycleChrono = millis();
      wateringState = WateringMachineStates::STATE_CYCLE_ON;
    }
    break;
  case (WateringMachineStates::STATE_CYCLE_ON):
    if (wateringCycleCount > WATERING_CYCLES)
    {
      wateringCycleCount = 0;
      wateringState = WateringMachineStates::STATE_WAIT;
    }
    if (millis() - wateringCycleChrono >= WATERING_CYCLE_DURATION)
    {
      wateringCyclePauseChrono = millis();
      wateringState = WateringMachineStates::STATE_CYCLE_PAUSE;
    }
    break;
  case (WateringMachineStates::STATE_CYCLE_PAUSE):
    if (millis() - wateringCyclePauseChrono >= WATERING_CYCLE_PAUSE_DURATION)
    {
      wateringCycleChrono = millis();
      wateringState = WateringMachineStates::STATE_CYCLE_ON;
    }
    break;

  default:
    break;
  }
}
/**
 * LIGHT MACHINE
 */
#define LIGHT_DURATION 3600000  //1h in ms
#define LIGHT_INTERVAL 86400000 //24h in ms
unsigned long lightChrono;
unsigned long lightOffChrono;

byte lightPin = 11;

void lightMachineInit()
{
  pinMode(lightPin, OUTPUT);
}
void lightMachine();
void lightMachine()
{

  switch (lightState)
  {
  case (LightStates::STATE_ON):
    digitalWrite(lightPin, LOW);
    if (wateringState == WateringMachineStates::STATE_WAIT && millis() - lightChrono >= LIGHT_DURATION)
    {
      lightTurnOff();
    }
    break;
  case (LightStates::STATE_OFF):
    digitalWrite(lightPin, HIGH);
    if (millis() - lightOffChrono >= LIGHT_INTERVAL)
    {
      lightTurnOn();
    }
    break;
  default:
    break;
  }
}
void lightTurnOn()
{
  lightState = LightStates::STATE_ON;
  lightChrono = millis();
}
void lightTurnOff()
{
  lightState = LightStates::STATE_OFF;
  lightOffChrono = millis();
}
/**
 * DISPLAY MACHINE
 */
#define DISPLAY_SLEEP_DELAY 60000
unsigned long sleepChrono;

unsigned long lastScreenOff = millis();
bool displayDisplayed = false;
bool displayNextState(DisplayStates state); // i beleive its arduino specific stuff, needed to pass Enum as parametr
bool displayNextState(DisplayStates state)
{
  if (switchState == SwitchStates::STATE_IS_FALLING)
  {
    displayState = state; // DisplayStates::STATE_MOISTURE;
    displayDisplayed = false;
    oled.set1X();
    oled.clear();
    sleepChrono = millis();
    return true;
  }
  return false;
}

void displaySleep()
{
  oled.ssd1306WriteCmd(0xAE);
}

void displayWake()
{
  oled.ssd1306WriteCmd(0xAF);
}
void displayWaterLevelInfo()
{

  oled.set2X();
  switch (waterLevelState)
  {
  case (WaterLevelStates::STATE_NOT_OK):
    oled.println("WATER LEVEL");
    oled.println();
    oled.println("NOT OK");

    break;
  case (WaterLevelStates::STATE_OK):
    oled.println("WATER LEVEL");
    oled.println();
    oled.println("OK");

    break;

  default:
    break;
  }
}
void displayWateringInfo()
{
  /**
   * 1.OFF
   * Watering is OFF
   * 
   * 2. CYCLE_ON
   * Watering is ON 
   * CYCLE 12/190
   * CYCLE ENDS IN 12s
   * 
   * 3. CYCLE_OFF
   * Watering is ON 
   * CYCLE 12/190
   * NEXT STARTS IN 12s
   */
  String wateringString = "Watering is ";
  String wateringONString = "ON";
  String wateringOFFString = "OFF";
  String wateringPAUSEDString = "PAUSED";
  String wateringNEXTString = "NEXT IN ";
  String wateringENDSString = "ENDS IN ";
  String wateringCYCLEString = "CYCLES";
  String wateringSlashString = "/";
  oled.set1X();
  switch (wateringState)
  {
  case (WateringMachineStates::STATE_WAIT):
    oled.println(wateringString);
    oled.println();
    oled.set2X();
    oled.println(wateringOFFString);
    /* code */
    break;
  case (WateringMachineStates::STATE_CYCLE_ON):
    oled.println(wateringONString);
    oled.println(wateringOFFString);
    oled.print(wateringENDSString + millisToTime(millis() - wateringCycleChrono));
    /* code */
    break;
  case (WateringMachineStates::STATE_CYCLE_PAUSE):
    oled.println(wateringString);
    oled.println(wateringPAUSEDString);
    oled.print(wateringNEXTString + millisToTime(millis() - wateringCyclePauseChrono));
    break;

  default:
    oled.set2X();
    oled.println("ERROR");
    oled.println("UNKNOWN");
    oled.println("STATUS");
    break;
  }
}
void displayMoistureInfo()
{

  /**
   * MOISTURE LEVEL
   * S1: 50 AVG:60
   * S2: 40 AVG:50
   * CRIT AVG: 40
   */

  oled.clear();
  oled.println("MOISTURE LEVEL");
  String s1 = "S1: ";
  String s2 = "S2: ";
  String avg = " AVG: ";
  //oled.set2X();
  oled.println();
  oled.println(s1 + moistureReadings[0][moistureReadingNumber - 1] + avg + moistureSensorAvg(0));
  oled.println(s1 + moistureReadings[1][moistureReadingNumber - 1] + avg + moistureSensorAvg(1));
  oled.set1X();
  oled.println();
  String crit = "CRIT AVG: ";
  oled.println(crit + WATERING_MOISTURE_CRITICAL);
}
void displayLightInfo()
{
  /**
   * 1.
   * LIGHT OF
   * ON IN 1233s 
   * 2.
   * LIGHT ON
   * OFF IN 1233s
   */
  String _stringLightOn = "LIGHT ON";
  String _stringLightOnIn = "ON IN ";
  String _stringLightOff = "LIGHT OFF";
  String _stringLightOffIn = "OFF IN ";
  switch (lightState)
  {
  case (LightStates::STATE_ON):
    oled.println(_stringLightOn);
    oled.println(_stringLightOffIn + millisToTime(LIGHT_DURATION - (millis() - lightChrono)));
    break;
  case (LightStates::STATE_OFF):
    oled.println(_stringLightOff);
    oled.println(_stringLightOnIn + millisToTime(LIGHT_INTERVAL - (millis() - lightOffChrono)));
    break;

  default:
    break;
  }
}
void displayMachineInit()
{
#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else  // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0

  oled.setFont(Adafruit5x7);

  uint32_t m = micros();
  oled.clear();
  oled.println("Welcome!");
  oled.set2X();
  oled.println("Watering System");
  oled.set1X();
  oled.println();
  oled.print("\nversion: ");
  oled.println(VERSION);
  oled.println("A long line may be truncated");

  delay(1000);
}
void checkSleep()
{
  if (displayState != DisplayStates::STATE_OFF && (millis() - sleepChrono >= DISPLAY_SLEEP_DELAY))
  {
    oled.clear();
    displayState = DisplayStates::STATE_OFF;
  }
}

void displayMachine()
{

  switch (displayState)
  {
  case (DisplayStates::STATE_OFF):
    displaySleep();
    if (displayNextState(DisplayStates::STATE_MOISTURE))
    {
      displayDisplayed = false;
      displayWake();
    }
    break;
  case (DisplayStates::STATE_MOISTURE):
    checkSleep();
    if (!displayDisplayed)
    {
      displayMoistureInfo();
      displayDisplayed = true;
    }
    displayNextState(DisplayStates::STATE_WATERING);

    break;
  case (DisplayStates::STATE_WATERING):
    checkSleep();

    if (!displayDisplayed)
    {
      displayWateringInfo();
      displayDisplayed = true;
    }
    displayNextState(DisplayStates::STATE_WATER_LEVEL);

    break;
  case (DisplayStates::STATE_WATER_LEVEL):
    checkSleep();

    if (!displayDisplayed)
    {
      displayWaterLevelInfo();
      displayDisplayed = true;
    }
    displayNextState(DisplayStates::STATE_LIGHT);

    break;
  case (DisplayStates::STATE_LIGHT):
    checkSleep();

    if (!displayDisplayed)
    {
      displayLightInfo();
      displayDisplayed = true;
    }
    displayNextState(DisplayStates::STATE_OFF);

    break;

  default:
    break;
  }
}
//if all your time calculations are done as:
//if  ((later_time - earlier_time ) >=duration ) {action}
//then the rollover does generally not come into play.

//unsigned long lastWateringTime=millis()-(waterEveryMinutes*60*1000);   // Time of last watering. Milliseconds since Arduino program has started.
//unsigned long wateringStartedTime=millis()-(wateringTimeInMinutes*60*1000);   //"ALWAYS use unsigned long for timers, not int"
String millisToTime(unsigned long milliseconds)
{

  //  Serial.println(milliseconds);
  int seconds = (int)(milliseconds / 1000) % 60;
  int minutes = (int)((milliseconds / (60000)) % 60);
  int hours = (int)((milliseconds / (3600000)) % 24);
  String timeString = "";
  timeString = timeString + hours + ":" + minutes + ":" + seconds;
  //Serial.println(timeString);

  return timeString;
}
void setup()
{
  Serial.begin(9600);

  // draw many lines
  moistureMachineInit();
  switchMachineInit();
  lightMachineInit();
  pumpMachineInit();
  wateringMachineInit();
  displayMachineInit();
}

void loop()
{
  switchMachine();
  moistureMachine();
  lightMachine();
  pumpMachine();
  wateringMachine();
  displayMachine();
}
