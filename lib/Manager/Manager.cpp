#include <Manager.h>

unsigned long Manager::currentTime;

StateMachine state;

int Manager::addressesFound[] = {0};

void Manager::startStateMachine() {
    Log::println("Setting state machine to state COLD_START");
    state = StateMachine::COLD_START;
}

int Manager::getState() {
    return state;
}

void Manager::setState(StateMachine st) {
    state = st;
}

void Manager::startSerial() {
    Serial.begin(BAUDRATE);
    
	while (!Serial) {
        delay(1);
    }
}

bool Manager::init() {
    Log::println("Initializing devices");
    if (
        initI2c() &&
        ina219.init() &&
        bmp388.init()
        ) {
        return true;
    } else {
        return false;
    }
}

void Manager::systemTest() {
    Log::println("\n--- RUNNING WHOLE SYSTEM TEST --- ");
    Log::println("# INA219 TEST #");
    ina219.update();
    ina219.printValues();
    Log::space();
    Log::println("# BMP388 TEST #");
    bmp388.update();
    bmp388.printValues();
    Log::println("--- DONE ---\n");
}

bool Manager::initI2c() {
    Wire.begin();
    
    Log::printSysln("I2C", "Verifying I2C bus");
    detectI2c();
    
    if (checkI2cBus()) {
        Log::printSysln("I2C", "Done");
        return true;
    } else {
        Log::printErrln("I2C", "Error detected in I2C");
        return false;
    }
}

bool Manager::checkI2cBus() {    
    int errorCounter = 0;
    for (unsigned int i = 0; i < sizeof(I2C_ADDRESSES)/sizeof(I2C_ADDRESSES[0]); i++) {
        if (I2C_ADDRESSES[i] != addressesFound[i]) {
            Log::printErr("I2C", "Device wrongly connected/missing | ");
            Serial.print("Found 0x");
            Serial.print(addressesFound[i], HEX);
            Serial.print("; expected 0x");
            Serial.println(I2C_ADDRESSES[i], HEX);
            errorCounter++;
        }
    }
    if (errorCounter == 0) {
        Log::printSysln("I2C", "No problems found");
        return true;
    } else { 
        return false;
    }
}

void Manager::detectI2c() {
    byte error, address;
    int nDevices;

    Log::printSysln("I2C", "Searching for devices...");

    nDevices = 0;
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();


        if (error == 0) {
            Log::printSys("I2C", "Device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
            addressesFound[nDevices] = address;
            nDevices++;
        } else if (error == 4) {
            Log::printSys("I2C", "Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0) {
        Log::printSysln("I2C", "No I2C devices found");
    }
    else {
        Log::printSysln("I2C", "Ended search");
    }
}

void Manager::startCountingTime() {
    currentTime = millis();
}

unsigned long Manager::getCurrentTime() {
    return currentTime;
}

void Manager::readSensors() {
    handleIna219();
    handleBmp388();
}

void Manager::handleIna219() {
    if (Manager::getCurrentTime() - ina219.previousTime >= INA_INTERVAL) {
        ina219.update();

        if (DEVELOPMENT) {
            Serial.println(Manager::getCurrentTime());
            ina219.printValues();
            if (ina219.isCharging()) {
                Log::printWarln("INA219", "Battery being charged");
            }
            Log::space();
        }

        ina219.validate();
        ina219.previousTime = currentTime;
    }

}

void Manager::handleBmp388() {
    if (Manager::getCurrentTime() - bmp388.previousTime >= BMP388_INTERVAL) {
        bmp388.update();

        if (DEVELOPMENT) {
            Serial.println(Manager::getCurrentTime());
            bmp388.printValues();
            Log::space();
        }

        bmp388.previousTime = currentTime;
    }
}