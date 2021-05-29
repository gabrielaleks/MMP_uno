#ifndef Bmp388_h
#define Bmp388_h
#include "Arduino.h"
#include "Adafruit_BMP3XX.h"
#include <Wire.h>
#include <Sensor.h>
#include <UserInterface.h>

class Bmp388: public Sensor, Adafruit_BMP3XX {
    private:
        bool isWorking;
        String statusMessage;
    public:
        bool init();
        void setSampling();
        void updateValues();
        double getTemperature();
        double getPressure();
        double getAltitude();
        void setIsWorking(bool status);
        bool getIsWorking();
        void printValues();
};

#endif