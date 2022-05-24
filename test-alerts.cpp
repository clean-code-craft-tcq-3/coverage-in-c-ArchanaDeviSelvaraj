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
  REQUIRE(classifyTemperatureBreachforPassiveCooling(HI_ACTIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(HI_ACTIVE_COOLING,45) == NORMAL);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(HI_ACTIVE_COOLING,-1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(HI_ACTIVE_COOLING,46) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(PASSIVE_COOLING,-15) == TOO_LOW);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(MED_ACTIVE_COOLING,-3) == TOO_LOW);
}

TEST_CASE("classifies Temperature Breach for MED_ACTIVE Cooling") {
  REQUIRE(classifyTemperatureBreachforPassiveCooling(MED_ACTIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(MED_ACTIVE_COOLING,40) == NORMAL);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(MED_ACTIVE_COOLING,-1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(MED_ACTIVE_COOLING,41) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(PASSIVE_COOLING,50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreachforPassiveCooling(HI_ACTIVE_COOLING,20) == NORMAL);
}
  
