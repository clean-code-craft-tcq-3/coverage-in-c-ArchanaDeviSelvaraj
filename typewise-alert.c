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

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  if(coolingType==PASSIVE_COOLING) 
    return inferBreach(temperatureInC, 0 , 35 );
  if(coolingType==HI_ACTIVE_COOLING) 
    return inferBreach(temperatureInC, 0 , 45 );
  if(coolingType==MED_ACTIVE_COOLING) 
    return inferBreach(temperatureInC, 0 , 40 );
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  switch(alertTarget) 
  {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  if(breachType==TOO_LOW) 
  {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
  }
   else if(breachType==TOO_HIGH)
   {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
   }
}
