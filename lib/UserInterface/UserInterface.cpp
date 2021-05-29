#include <Arduino.h>
#include <UserInterface.h>

void UserInterface::printSys(String system, String message) {
    Serial.print("[" + system + "]" + " " + message);
}

void UserInterface::printSysln(String system, String message) {
    Serial.println("[" + system + "]" + " " + message);
}

void UserInterface::printErr(String system, String message) {
    Serial.print("[" + system + "]" + " [ERROR] " + message);
}

void UserInterface::printErrln(String system, String message) {
    Serial.println("[" + system + "]" + " [ERROR] " + message);
}