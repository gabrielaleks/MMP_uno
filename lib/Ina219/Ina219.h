#ifndef Ina219_h
#define Ina219_h
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Sensor.h>
#include <UserInterface.h>

class Ina219: private Sensor, Adafruit_INA219 {
private:
    bool isWorking = false;
    void setIsWorking(bool);
    void setData();
public:
    bool init();
    double getBusVoltage();
    double getShuntVoltage();
    double getLoadVoltage();
    double getCurrent();
    double getPower();
    void printValues();
    byte getAddress();
};

#endif