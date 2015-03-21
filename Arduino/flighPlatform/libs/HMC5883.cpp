#include "HMC5883.h"
#include <Wire.h> //I2C Arduino Library

HMC5883::HMC5883() {
}

void HMC5883::enableDefault() {
    Wire.begin();

    Wire.beginTransmission(HMC5883_ADDRESS); //open communication with HMC5883
    Wire.write(0x02); //select mode register
    Wire.write(0x00); //continuous measurement mode
    Wire.endTransmission();
}

void HMC5883::read() {
    int x, y, z = 0; //triple axis data

    //Tell the HMC5883 where to begin reading data
    Wire.beginTransmission(HMC5883_ADDRESS);
    Wire.write(0x03); //select register 3, X MSB register
    Wire.endTransmission();

    //Read data from each axis, 2 registers per axis
    Wire.requestFrom(HMC5883_ADDRESS, 6);
    if (6 <= Wire.available()) {
        x = Wire.read() << 8; //X msb
        x |= Wire.read(); //X lsb
        z = Wire.read() << 8; //Z msb
        z |= Wire.read(); //Z lsb
        y = Wire.read() << 8; //Y msb
        y |= Wire.read(); //Y lsb
    }

    g.x = x;
    g.y = y;
    g.z = z;
}
