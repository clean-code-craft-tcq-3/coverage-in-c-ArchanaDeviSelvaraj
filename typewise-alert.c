#include "typewise-alert.h"
#include <stdio.h>

int BreachLimitforCoolingTypeTemp[3][2] ={{0,35},{0,40},{0,45}};

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

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  int lowerLimit = 0;
  int upperLimit = 0;
  lowerLimit = BreachLimitforCoolingTypeTemp[(int)coolingType][0];
  upperLimit = BreachLimitforCoolingTypeTemp[(int)coolingType][1];
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
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
