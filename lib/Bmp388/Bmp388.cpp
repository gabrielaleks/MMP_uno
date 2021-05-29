#include <Arduino.h>
#include <Bmp388.h>

bool Bmp388::init() {
    if (!begin_I2C(BMP388_ADDR)) {
        // Serial.println("BMP388: Failed to initialize");
        UserInterface::printSysln("BMP388", "Failed to initialize");
        setIsWorking(false);
    } else {
        // Serial.println("BMP388: Success");
        UserInterface::printSysln("BMP388", "Success");
        setIsWorking(true);
    }
}

void Bmp388::setIsWorking(bool status) {
    isWorking = status;
}

bool Bmp388::getIsWorking() {
    return isWorking;
}

void Bmp388::setSampling() {
    setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    setPressureOversampling(BMP3_OVERSAMPLING_4X);
    setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    setOutputDataRate(BMP3_ODR_50_HZ);
}

void Bmp388::updateValues() {
    if (!performReading()) {
        // Serial.println("BMP388: Failed to perform reading");
        UserInterface::printSysln("BMP388", "Failed to perform reading");
        return;
    }
}

double Bmp388::getTemperature() {
    // Serial.print("Temperature: ");
    // Serial.println(temperature);
    return temperature;
}

double Bmp388::getPressure() {
    // Serial.print("Pressure: ");
    // Serial.println(pressure/100);
    return pressure/100;
}

double Bmp388::getAltitude() {
    // Serial.print("Altitude: ");
    // Serial.println(readAltitude(SEALEVELPRESSURE_HPA));
    return readAltitude(SEALEVELPRESSURE_HPA);
}

void Bmp388::printValues() {
//     cout << "Temperature   " << getBusVoltage() << " V" << endl;
//     cout << "Pressure: " << getShuntVoltage() << " mV" << endl;
//     cout << "Altitude:  " << getLoadVoltage() << " V" << endl;
//     cout << "" << endl;
    Serial.println("Temperature: " + String(getTemperature()) + " C");
    Serial.println("Pressure: " + String(getPressure()) + " hPa");
    Serial.println("Altitude: " + String(getAltitude()) + " m");
    Serial.println();
}