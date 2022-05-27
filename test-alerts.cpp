#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
  REQUIRE(inferBreach(30, 20, 30) == NORMAL);
  REQUIRE(inferBreach(19, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(31, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(21, 20, 30) == NORMAL);
  REQUIRE(inferBreach(29, 20, 30) == NORMAL);
}

TEST_CASE("classifies Temperature Breach") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,10) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,40) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,10) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-10) == TOO_LOW);,
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,45) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,46) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,10) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,45) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,40) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,41) == TOO_HIGH);
}
  
TEST_CASE("checks and alerts if there is temperature breach") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -15) == SENT_TEMP_LOW_TO_CONTROLLER);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, -15) == SENT_TEMP_LOW_ALERT) ;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 65) == SENT_TEMP_HIGH_TO_CONTROLLER);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 65) == SENT_TEMP_HIGH_ALERT);
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 25) == NORMAL_NO_ALERT);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 25) == NORMAL_NO_ALERT);
  checkAndAlert(NO_ALERT, batteryChar, 25);
}

TEST_CASE("sends alert to controller") {
  REQUIRE(sendToController(TOO_LOW) == SENT_TEMP_LOW_TO_CONTROLLER);
  REQUIRE(sendToController(TOO_HIGH) == SENT_TEMP_HIGH_TO_CONTROLLER);
  REQUIRE(sendToController(NORMAL) == NORMAL_NO_ALERT);
}

TEST_CASE("sends alert in mail") {
  REQUIRE(sendToEmail(TOO_LOW) == SENT_TEMP_LOW_ALERT);
  REQUIRE(sendToEmail(TOO_HIGH) == SENT_TEMP_HIGH_ALERT);
  REQUIRE(sendToEmail(NORMAL) == NORMAL_NO_ALERT);
}

  
  
