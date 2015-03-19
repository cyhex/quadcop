#include "ADXL345.h"


//void ADXL345::enableDefault(void)
//{
// enable to measute g data
//Wire.beginTransmission(ADXAddress);
//Wire.send(Register_2D);
//Wire.send(8); //measuring enable
//Wire.endTransmission(); // stop transmitting
//}

//void ADXL345::read(void) {
//--------------X
//Wire.beginTransmission(ADXAddress); // transmit to device
//Wire.send(Register_X0);
//Wire.send(Register_X1);
//Wire.endTransmission();
//    Wire.requestFrom(ADXAddress, 2);
//    if (Wire.available() <= 2) {
//        int X0 = Wire.receive();
//        int X1 = Wire.receive();
//        X1 = X1 << 8;
//        int X_out = X0 + X1;
//    }
//
//    //------------------Y
//    Wire.beginTransmission(ADXAddress); // transmit to device
//    Wire.send(Register_Y0);
//    Wire.send(Register_Y1);
//    Wire.endTransmission();
//    Wire.requestFrom(ADXAddress, 2);
//    if (Wire.available() <= 2) {
//        int Y0 = Wire.receive();
//        int Y1 = Wire.receive();
//        Y1 = Y1 << 8;
//        int Y_out = Y0 + Y1;
//    }
//    //------------------Z
//    Wire.beginTransmission(ADXAddress); // transmit to device
//    Wire.send(Register_Z0);
//    Wire.send(Register_Z1);
//    Wire.endTransmission();
//    Wire.requestFrom(ADXAddress, 2);
//    if (Wire.available() <= 2) {
//        int Z0 = Wire.receive();
//        int Z1 = Wire.receive();
//        Z1 = Z1 << 8;
//        int Z_out = Z0 + Z1;
//    }
//    g.x = X_out / 256.0;
//    g.y = Y_out / 256.0;
//    g.z = Z_out / 256.0;
//}