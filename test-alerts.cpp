#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("classifies Temperature Breach") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,10) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,40) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,10) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,10) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,45) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-10) == TOO_LOW);
}

TEST_CASE("classifies Temperature Breach for Passive Cooling") {
  REQUIRE(classifyTemperatureBreachforPassiveCooling(PASSIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(PASSIVE_COOLING,35) == NORMAL);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(PASSIVE_COOLING,-1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(PASSIVE_COOLING,36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(HI_ACTIVE_COOLING,46) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(MED_ACTIVE_COOLING,30) == NORMAL);
}

TEST_CASE("classifies Temperature Breach for HI_Active Cooling") {
  REQUIRE(classifyTemperatureBreachforHI_ActiveCooling(HI_ACTIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreachforHI_ActiveCooling(HI_ACTIVE_COOLING,45) == NORMAL);
  REQUIRE(classifyTemperatureBreachforHI_ActiveCooling(HI_ACTIVE_COOLING,-1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreachforHI_ActiveCooling(HI_ACTIVE_COOLING,46) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreachforHI_ActiveCooling(MED_ACTIVE_COOLING,-3) == TOO_LOW);
  //below testcase not possible, just added for coverage
  REQUIRE(classifyTemperatureBreachforHI_ActiveCooling(PASSIVE_COOLING,-15) == NONE);
  
}

TEST_CASE("classifies Temperature Breach for MED_ACTIVE Cooling") {
  REQUIRE(classifyTemperatureBreachforMED_ACTIVECooling(MED_ACTIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreachforMED_ACTIVECooling(MED_ACTIVE_COOLING,40) == NORMAL);
  REQUIRE(classifyTemperatureBreachforMED_ACTIVECooling(MED_ACTIVE_COOLING,-1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreachforMED_ACTIVECooling(MED_ACTIVE_COOLING,41) == TOO_HIGH);
  //below two scenarios not possible, just added for coverage
  REQUIRE(classifyTemperatureBreachforMED_ACTIVECooling(PASSIVE_COOLING,50) == NONE);
  REQUIRE(classifyTemperatureBreachforMED_ACTIVECooling(HI_ACTIVE_COOLING,20) == NONE);
}

TEST_CASE("if cooling type not available") {
  REQUIRE(classifyTemperatureBreachforPassiveCooling(COOLING_TYPE_NOT_DEFINED,0) == NONE);
  REQUIRE(classifyTemperatureBreachforHI_ActiveCooling(COOLING_TYPE_NOT_DEFINED,-1) == NONE);
  REQUIRE(classifyTemperatureBreachforMED_ACTIVECooling(COOLING_TYPE_NOT_DEFINED,41) == NONE);
}
  
TEST_CASE("checks and alerts if there is temperature breach") {
  BatteryCharacter coolingType = {PASSIVE_COOLING};
  checkAndAlert(TO_CONTROLLER, batteryChar, -15);
  checkAndAlert(TO_EMAIL, batteryChar, -15);
}
  
  
