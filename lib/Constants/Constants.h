#ifndef Constants_h
#define Constants_h

#define INA219_ADDR                 0x40
#define MPU9250_ADDR                0x68
#define BMP280_ADDR                 0x76
#define BMP388_ADDR                 0x77

const int I2CADDRESSES[4] = {
    INA219_ADDR,
    MPU9250_ADDR,
    BMP280_ADDR,
    BMP388_ADDR
};

#define SEALEVELPRESSURE_HPA        1013.25

#endif