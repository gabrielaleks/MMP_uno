#ifndef SensorInterface_h
#define SensorInterface_h
#include <Arduino.h>
#include <Wire.h>
#include <sdios.h>
#include <Constants.h>

class SensorInterface {
    public:
        virtual bool init();
        // void printSys(String, String);
};

#endif