#include "ADXL345.h"
#include <Wire.h>

#define ADXAddress (0xA7 >> 1)

ADXL345::ADXL345() {
}

void ADXL345::enableDefault() {
    // enable to measute g data
    Wire.beginTransmission(ADXAddress);
    Wire.write(Register_2D);
    Wire.write(8); //measuring enable
    Wire.endTransmission(); // stop transmitting
}

void ADXL345::read() {

    int X0, X1, X_out;
    int Y0, Y1, Y_out;
    int Z1, Z0, Z_out;

    //--------------X
    Wire.beginTransmission(ADXAddress); // transmit to device
    Wire.write(Register_X0);
    Wire.write(Register_X1);
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
    Wire.write(Register_Y0);
    Wire.write(Register_Y1);
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
    Wire.write(Register_Z0);
    Wire.write(Register_Z1);
    Wire.endTransmission();
    Wire.requestFrom(ADXAddress, 2);
    if (Wire.available() <= 2) {
        Z0 = Wire.read();
        Z1 = Wire.read();
        Z1 = Z1 << 8;
        Z_out = Z0 + Z1;
    }
    g.x = X_out / 256.0;
    g.y = Y_out / 256.0;
    g.z = Z_out / 256.0;
}
