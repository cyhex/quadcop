#include <Arduino.h>
#include <Wire.h>
#include "libs/ADXL345.h"
#include "libs/L3G4200D.h"
#include "libs/PID.h"
#include "libs/HMC5883.h"
#include "libs/Tilt.h"
extern HardwareSerial Serial;

L3G4200D gyro;
ADXL345 accel;
HMC5883 mag;
Tilt tilt;

PID pid;

unsigned long lastPrint = 0;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    accel.enableDefault();
    gyro.enableDefault();
    mag.enableDefault();
    pid.run(0.0, 0.0);
}
/**
 * print only once in 100 ms 
 */
void printOut() {

    if ((millis() - lastPrint) < 100) {
        return;
    }
    lastPrint = millis();
    
    Serial.print("x: ");
    Serial.print(tilt.tilt.x);

    Serial.print(" y: ");
    Serial.print(tilt.tilt.y);
    
    //    Serial.print("gyr ");
    //    Serial.print("X: ");
    //    Serial.print((int) gyro.g.x);
    //    Serial.print(" Y: ");
    //    Serial.print((int) gyro.g.y);
    //    Serial.print(" Z: ");
    //    Serial.println((int) gyro.g.z);

    //    Serial.print("acc ");
    //    Serial.print("X: ");
    //    Serial.print(accel.pos.x);
    //    Serial.print(" Y: ");
    //    Serial.print(accel.pos.y);
    //    Serial.print(" Z: ");
    //    Serial.println(accel.pos.z);

    //    Serial.print("mag ");
    //    Serial.print("X: ");
    //    Serial.print(mag.g.x);
    //    Serial.print(" Y: ");
    //    Serial.print(mag.g.y);
    //    Serial.print(" Z: ");
    //    Serial.println(mag.g.z);
}

void loop() {
    accel.read();
    gyro.read();
    mag.read();
    tilt.calculate(accel.pos, gyro.g, mag.g);
    printOut();
}

