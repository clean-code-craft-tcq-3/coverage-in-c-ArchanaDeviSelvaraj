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
