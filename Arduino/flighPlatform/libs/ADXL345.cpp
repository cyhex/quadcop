#include "ADXL345.h"
#include <Wire.h>

#define ADXAddress (0xA7 >> 1)

ADXL345::ADXL345() {
}

void ADXL345::enableDefault() {
    // enable to measure g data
    Wire.beginTransmission(ADXAddress);
    Wire.write(ADXL345_REG_POWER_CTL);
    Wire.write(8); //measuring enable

    // set data range
    range_t range = ADXL345_RANGE_2_G;
    Wire.write(ADXL345_REG_DATA_FORMAT);
    Wire.write(range);

    // set data rate
    dataRate_t dataRate = ADXL345_DATARATE_0_10_HZ;
    Wire.write(ADXL345_REG_BW_RATE);
    Wire.write(dataRate);

    Wire.endTransmission();
}

void ADXL345::read() {

    int X0, X1, X_out = 0;
    int Y0, Y1, Y_out = 0;
    int Z1, Z0, Z_out = 0;

    //--------------X
    Wire.beginTransmission(ADXAddress); // transmit to device
    Wire.write(ADXL345_REG_DATAX0);
    Wire.write(ADXL345_REG_DATAX1);
    Wire.endTransmission();
    Wire.requestFrom(ADXAddress, 2);
    if (Wire.available() <= 2) {
        X0 = Wire.read();
        X1 = Wire.read();
        X1 = X1 << 8;
        X_out = X0 + X1;
    }

    //------------------Y
    Wire.beginTransmission(ADXAddress); // transmit to device
    Wire.write(ADXL345_REG_DATAY0);
    Wire.write(ADXL345_REG_DATAY1);
    Wire.endTransmission();
    Wire.requestFrom(ADXAddress, 2);
    if (Wire.available() <= 2) {
        Y0 = Wire.read();
        Y1 = Wire.read();
        Y1 = Y1 << 8;
        Y_out = Y0 + Y1;
    }
    //------------------Z
    Wire.beginTransmission(ADXAddress); // transmit to device
    Wire.write(ADXL345_REG_DATAZ0);
    Wire.write(ADXL345_REG_DATAZ1);
    Wire.endTransmission();
    Wire.requestFrom(ADXAddress, 2);
    if (Wire.available() <= 2) {
        Z0 = Wire.read();
        Z1 = Wire.read();
        Z1 = Z1 << 8;
        Z_out = Z0 + Z1;
    }
    pos.x = X_out * ADXL345_SENSITIVITY_MULTIPLIER;
    pos.y = Y_out * ADXL345_SENSITIVITY_MULTIPLIER;
    pos.z = Z_out * ADXL345_SENSITIVITY_MULTIPLIER;
    
    // acceleration in m/s^2 
    acc.x = X_out * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
    acc.y = Y_out * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
    acc.z = Z_out * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
    
}
