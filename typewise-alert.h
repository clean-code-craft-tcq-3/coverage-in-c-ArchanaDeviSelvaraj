#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  COOLING_TYPE_NOT_DEFINED
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
  NONE
} BreachType;

typedef enum {
  SENT_TEMP_LOW_TO_CONTROLLER,
  SENT_TEMP_HIGH_TO_CONTROLLER,
  SENT_TEMP_LOW_ALERT,
  SENT_TEMP_HIGH_ALERT,
  NORMAL_NO_ALERT,
  NO_ALERT_TARGET
} AlertType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreachforPassiveCooling(CoolingType coolingType, double temperatureInC);
BreachType classifyTemperatureBreachforHI_ActiveCooling(CoolingType coolingType, double temperatureInC);
BreachType classifyTemperatureBreachforMED_ACTIVECooling(CoolingType coolingType, double temperatureInC);
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
