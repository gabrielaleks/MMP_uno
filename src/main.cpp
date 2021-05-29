#include <Arduino.h>
#include <Manager.h>
#include <Ina219.h>
#include <Bmp388.h>
#include <Adafruit_INA219.h>

Manager manager;
Bmp388 bmp;

void setup(void) {
    Serial.begin(9600);
    
	while (!Serial) {
        delay(1);
    }
    // ina.begin();
    // Serial.println(ina.getBusVoltage_V());
    manager.init();
    manager.systemTest();
    // bmp.init();
    // bmp.setSampling();
    // if(!manager.checkI2cDevices()) {
    //     Serial.println("deu ruim");
    // } else {
    //     Serial.println("deu bom");
    // }
}

void loop(void) {
    // bmp.updateValues();
    // bmp.printValues();
    // delay(1000);
}