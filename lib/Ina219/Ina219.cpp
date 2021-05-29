#include <Arduino.h>
#include <Ina219.h>

bool Ina219::init() {
    if (!begin()) {
        Serial.println("Failed to find INA219 chip");
        while (1)
        {
            delay(10);
        }
        return false;
    } else {
        UserInterface::printSysln("INA219", "Success");
        return true;
    }
}

void Ina219::setIsWorking(bool state) {
    isWorking = state;
}

double Ina219::getBusVoltage() {
    return getBusVoltage_V();
}

double Ina219::getShuntVoltage() {
    return getShuntVoltage_mV();
}

double Ina219::getLoadVoltage() {
    return getBusVoltage() + (getShuntVoltage() / 1000);
}

double Ina219::getCurrent() {
    return getCurrent_mA();
}

double Ina219::getPower() {
    return getPower_mW();
}

void Ina219::printValues() {
    Serial.println("Bus Voltage: " + String(getBusVoltage()) + " V");
    Serial.println("Shunt Voltage: " + String(getShuntVoltage()) + " mV");
    Serial.println("Load Voltage: " + String(getLoadVoltage()) + " V");
    Serial.println("Current: " + String(getCurrent()) + " mA");
    Serial.println("Power: " + String(getPower()) + " mW");
    Serial.println();
}