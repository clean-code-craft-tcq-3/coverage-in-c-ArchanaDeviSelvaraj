#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreachforPassiveCooling(CoolingType coolingType, double temperatureInC) 
{
  if(coolingType==PASSIVE_COOLING) 
    return inferBreach(temperatureInC, 0 , 35 );
  else
    return classifyTemperatureBreachforHI_ActiveCooling(coolingType, temperatureInC);
}
BreachType classifyTemperatureBreachforHI_ActiveCooling(CoolingType coolingType, double temperatureInC) 
{
  if(coolingType==HI_ACTIVE_COOLING) 
    return inferBreach(temperatureInC, 0 , 45 );
  else
    return classifyTemperatureBreachforMED_ACTIVECooling(coolingType, temperatureInC);
}
BreachType classifyTemperatureBreachforMED_ACTIVECooling(CoolingType coolingType, double temperatureInC) 
{
  if(coolingType==MED_ACTIVE_COOLING) 
     return inferBreach(temperatureInC, 0 , 40 );
  else
    return NONE;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  return classifyTemperatureBreachforPassiveCooling(coolingType, temperatureInC); 
 }


AlertType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  switch(alertTarget) 
  {
    case TO_CONTROLLER:
      return sendToController(breachType);
      break;
    case TO_EMAIL:
      return sendToEmail(breachType);
      break;
    case default:
      return NO_ALERT_TARGET;
  }
}

AlertType sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  if(breachType == TOO_LOW)
    return SENT_TEMP_LOW_TO_CONTROLLER;
  else if(breachType == TOO_HIGH)
    return SENT_TEMP_HIGH_TO_CONTROLLER;
  else
    return NORMAL_NO_ALERT;
}

AlertType sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  if(breachType==TOO_LOW) 
  {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      return SENT_TEMP_LOW_ALERT;
  }
   else if(breachType==TOO_HIGH)
   {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      return SENT_TEMP_HIGH_ALERT;
   }
       else
         return NORMAL_NO_ALERT;
}
