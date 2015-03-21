#include "Postion.h"
#include <Arduino.h>
#include <math.h>

Postion::Postion() {
    lastTime = millis();
}

void Postion::calculate(ADXL345 acc, L3G4200D gyro, HMC5883 mag) {
    acc.read();
    gyro.read();
    mag.read();

    // calculate accelerometers pitch and roll in deg
    float apitch = atan2(acc.pos.y, acc.pos.z) * RAD_TO_DEG;
    float aroll = atan2(acc.pos.x, acc.pos.z) * RAD_TO_DEG;

    // calculate delta time since last run in seconds
    float dt = (millis() - lastTime) / 1000.0;

    // calculate gyro change pitch and roll (in degrees)
    float gpitch = gyro.g.x * dt;
    float groll = gyro.g.y * dt;

    // calculate pitch angle in degrees
    pitch = POSITION_GYR_RATIO * (pitch + gpitch) + (1 - POSITION_GYR_RATIO) * apitch;

    // calculate roll angle in degrees
    roll = POSITION_GYR_RATIO * (roll + groll) + (1 - POSITION_GYR_RATIO) * aroll;

    lastTime = millis();
}
