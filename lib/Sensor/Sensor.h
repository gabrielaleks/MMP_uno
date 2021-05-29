#ifndef Sensor_h
#define Sensor_h
#include <Arduino.h>
#include <Wire.h>
#include <sdios.h>
#include <Constants.h>

class Sensor {
    public:
        virtual bool init();
        // void printSys(String, String);
};

#endif