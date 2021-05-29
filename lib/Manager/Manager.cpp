#include <Manager.h>

int Manager::addressesFound[] = {0};

bool Manager::init() {
    Serial.println("\n--- INITIALIZING ---");
    // Inicializar i2c
    initI2c();
    // Inicializar interface
    // led.setLedPin(10);

    // Inicializar ina219
    ina219.init();

    // Inicializar bmp388
    bmp388.init();
    bmp388.setSampling();
    Serial.println("--- DONE ---\n");
}

bool Manager::systemTest() {
    Serial.println("--- RUNNING WHOLE SYSTEM TEST --- ");
    Serial.println("# INA219 TEST #");
    ina219.printValues();
    Serial.println("# BMP388 TEST #");
    bmp388.updateValues();
    bmp388.printValues();

    Serial.println("--- DONE ---");
}

bool Manager::initI2c() {
    Wire.begin();
    // Serial.println("\nVERIFYING I2C BUS");
    UserInterface::printSysln("I2C", "Verifying I2C bus");
    detectI2c();
    checkI2cDevices();
    // Serial.println("DONE");
    UserInterface::printSysln("I2C", "Done");
}

bool Manager::checkI2cDevices() {    
    int errorCounter = 0;
    for (unsigned int i = 0; i < sizeof(I2CADDRESSES)/sizeof(I2CADDRESSES[0]); i++) {
        // Serial.println(I2CADDRESSES[i], HEX);
        // Serial.println(addressesFound[i], HEX);
        // if (I2CADDRESSES[i] != addressesFound[i] && addressesFound[i] != 0) {
        //     UserInterface::printErr("I2C", "Device incorrectly connected to address 0X");
        //     Serial.print(addressesFound[i], HEX);
        //     Serial.print("; should be connected to 0X");
        //     Serial.println(I2CADDRESSES[i], HEX);
        //     errorCounter++;
        // } else if (I2CADDRESSES[i] != addressesFound[i] && addressesFound[i] == 0) {
        //     UserInterface::printErr("I2C", "Missing device; should be connected to 0X");
        //     Serial.println(I2CADDRESSES[i], HEX);
        //     errorCounter++;
        // }
        if (I2CADDRESSES[i] != addressesFound[i]) {
            UserInterface::printErr("I2C", "Device wrongly connected/missing | ");
            Serial.print("Found 0x");
            Serial.print(addressesFound[i], HEX);
            Serial.print("; expected 0x");
            Serial.println(I2CADDRESSES[i], HEX);
            errorCounter++;
        }
    }
    if (errorCounter == 0) {
        // Serial.println("No problems found");
        UserInterface::printSysln("I2C", "No problems found");
        return 1;
    } else { 
        return 0;
    }
}

void Manager::detectI2c() {
    byte error, address;
    int nDevices;

    UserInterface::printSysln("I2C", "Searching for devices...");

    nDevices = 0;
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();


        if (error == 0) {
            // Serial.print("I2C device found at address 0x");
            UserInterface::printSys("I2C", "Device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
            addressesFound[nDevices] = address;
            nDevices++;
        } else if (error == 4) {
            // Serial.print("Unknown error at address 0x");
            UserInterface::printSys("I2C", "Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0) {
        // Serial.println("No I2C devices found");
        UserInterface::printSysln("I2C", "No I2C devices found");
    }
    else {
        // Serial.println("Ended search");
        UserInterface::printSysln("I2C", "Ended search");
    }
}
