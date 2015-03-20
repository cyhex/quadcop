/* 
 * File:   Tilt.cpp
 * Author: gx
 * 
 * Created on March 20, 2015, 4:22 PM
 */

#include "Tilt.h"

Tilt::Tilt() {
    lastTime = millis();
}

void Tilt::calculate(ADXL345::vector vectorAccel, L3G4200D::vector vectorGyro, HMC5883::vector vectorMag) {

    // calculate accelerometer's pith and roll
    float pitch = atan2(vectorAccel.y, vectorAccel.z) * RAD_TO_DEG;
    float roll = atan2(vectorAccel.x, vectorAccel.z) * RAD_TO_DEG;

    // calculate delta time since last run in seconds
    float dt = (millis() - lastTime) / 1000.0;

    // calculate X angle in degrees
    tilt.x = 0.98 * (tilt.x + vectorGyro.x * dt) + 0.02 * pitch;

    // calculate Y angle in degrees
    tilt.y = 0.98 * (tilt.y + vectorGyro.y * dt) + 0.02 * roll;

    lastTime = millis();
}