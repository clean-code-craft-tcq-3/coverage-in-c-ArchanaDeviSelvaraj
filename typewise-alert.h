#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  SENT_TEMP_LOW_TO_CONTROLLER,
  SENT_TEMP_HIGH_TO_CONTROLLER,
  SENT_TEMP_LOW_ALERT,
  SENT_TEMP_HIGH_ALERT,
  NORMAL_NO_ALERT
} AlertType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  NO_ALERT
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

AlertType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
AlertType sendToController(BreachType breachType);
AlertType sendToEmail(BreachType breachType);
