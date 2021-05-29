#ifndef Manager_h
#define Manager_h
#include "Arduino.h"
#include <Bmp388.h>
#include <Led.h>
#include <Ina219.h>
#include <Constants.h>
#include <string.h>

class Manager {
private:
    static int addressesFound[4];
    bool checkI2cDevices();
    void identifyI2cError();
protected:
    float status;
    unsigned long interval = 1000;
    unsigned long previousTime;    
    Led led;
    Bmp388 bmp388;
    Ina219 ina219;   
public:
    bool init();
    bool systemTest();
    bool initI2c();
    static void detectI2c();
};

#endif