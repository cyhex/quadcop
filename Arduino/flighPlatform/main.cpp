#include <Arduino.h>
#include <Wire.h>
#include "helpers/ADXL345.h"
#include "helpers/L3G4200D.h"
#include "helpers/PID.h"
#include "helpers/HMC5883.h"
#include "helpers/Tilt.h"
extern HardwareSerial Serial;

L3G4200D gyro;
ADXL345 accel;
HMC5883 mag;
Tilt tilt;

PID pid;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    accel.enableDefault();
    gyro.enableDefault();
    mag.enableDefault();
    pid.run(0.0, 0.0);
}

void loop() {
    accel.read();
    gyro.read();
    mag.read();
    tilt.calculate(accel.g, gyro.g, mag.g);
    
    Serial.print("gyro ");
    Serial.print("X: ");
    Serial.print((int) gyro.g.x);
    Serial.print(" Y: ");
    Serial.print((int) gyro.g.y);
    Serial.print(" Z: ");
    Serial.println((int) gyro.g.z);

    Serial.print("accel ");
    Serial.print("X: ");
    Serial.print(accel.g.x);
    Serial.print(" Y: ");
    Serial.print(accel.g.y);
    Serial.print(" Z: ");
    Serial.println(accel.g.z);

    delay(500);
}