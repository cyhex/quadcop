#include <Arduino.h>
#include <Wire.h>
#include "helpers/ADXL345.h"
#include "helpers/L3G4200D.h"
#include "helpers/PID.h"

extern HardwareSerial Serial;

L3G4200D gyro;
ADXL345 accel;

PID pid;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    //accel.enableDefault();
    gyro.enableDefault();
    pid.run(0.0, 0.00);
}

void loop() {
    //accel.read();
    gyro.read();
    Serial.print("gyro ");
    Serial.print("X: ");
    Serial.print((int) gyro.g.x);
    Serial.print(" Y: ");
    Serial.print((int) gyro.g.y);
    Serial.print(" Z: ");
    Serial.println((int) gyro.g.z);
    
    Serial.print("accel ");
    Serial.print("X: ");
    //Serial.print((int) accel.g.x);
    Serial.print(" Y: ");
    //Serial.print((int) accel.g.y);
    Serial.print(" Z: ");
    //Serial.println((int) accel.g.z);

    delay(500);
}