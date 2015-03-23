#include "HMC5883.h"
#include <Wire.h>
#include <Arduino.h> //I2C Arduino Library

HMC5883::HMC5883() {
}

void HMC5883::enableDefault() {
    Wire.begin();

    Wire.beginTransmission(HMC5883_ADDRESS); //open communication with HMC5883
    Wire.write(0x02); //select mode register
    Wire.write(0x00); //continuous measurement mode
    Wire.write(0b00100000); // 1.3 gain LSb / Gauss 1090 (default)
    Wire.write(0b01110000); // Set to 8 samples @ 15Hz
    Wire.endTransmission();
    c.maxx, c.maxy, c.maxz, c.minx, c.miny, c.minz = 0;

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
        g.x = (x - c.offsetx) * HMC5883_SCALE;
        g.y = (y - c.offsety) * HMC5883_SCALE;
        g.z = (z - c.offsetz) * HMC5883_SCALE;
    }


}

void HMC5883::calibrate() {

    for (int i = 0; i < 1500; i++) {
        read();
        if (g.x < c.minx) {
            c.minx = g.x;
        }

        if (g.y < c.miny) {
            c.miny = g.y;
        }
        if (g.z < c.minz) {
            c.minz = g.z;
        }

        if (g.x > c.maxx) {
            c.maxx = g.x;
        }

        if (g.y > c.maxy) {
            c.maxy = g.y;
        }

        if (g.z > c.maxz) {
            c.maxz = g.z;
        }
        delay(10);
    }

    c.offsetx = (c.maxx + c.minx) * 0.5;
    c.offsety = (c.maxy + c.miny) * 0.5;
    c.offsetz = (c.maxz + c.minz) * 0.5;

}