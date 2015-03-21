#include <Arduino.h>
#include <Wire.h>
#include "libs/ADXL345.h"
#include "libs/L3G4200D.h"
#include "libs/PID.h"
#include "libs/HMC5883.h"
#include "libs/Postion.h"
extern HardwareSerial Serial;

L3G4200D gyro;
ADXL345 accel;
HMC5883 mag;
Postion pos;

PID pid;

unsigned long lastPrint = 0;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    accel.enableDefault();
    gyro.enableDefault();
    mag.enableDefault();
    pid.run(0.0, 0.0);
    Serial.println("Calibrate compass: tilt and move for 30 sec");
}
/**
 * print only once in 100 ms 
 */
void printOut() {

    if ((millis() - lastPrint) < 300) {
        return;
    }
    lastPrint = millis();
    
    Serial.print("pitch: ");
    Serial.print(pos.pitch);

    Serial.print(" roll: ");
    Serial.print(pos.roll);
    
    Serial.print(" heading: ");
    Serial.println(pos.heading);
    
    mag.read();
    Serial.print("mag x: ");
    Serial.print(mag.g.x );
    
    Serial.print(" y: ");
    Serial.print(mag.g.y );
    
    Serial.print(" z: ");
    Serial.println(mag.g.z);
}

void loop() {
    pos.calculate(accel, gyro, mag);
    printOut();
}

