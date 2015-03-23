#include <Arduino.h>
#include <Wire.h>
#include "libs/ADXL345.h"
#include "libs/L3G4200D.h"
#include "libs/PID.h"
#include "libs/HMC5883.h"
#include "libs/Postion.h"
#include "libs/HCSRC04.h"
extern HardwareSerial Serial;

L3G4200D gyro;
ADXL345 accel;
HMC5883 mag;
Postion pos;
HCSRC04 ping;
PID pid;

unsigned long lastPrint = 0;
unsigned long lastCycle= 0;
unsigned long cycleCount = 0;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    accel.enableDefault();
    gyro.enableDefault();
    mag.enableDefault();
    ping.enableDefault();
//    Serial.println("mag callibration");
//    mag.calibrate();
//    Serial.println("mag callibration done");
}

/**
 * print only once in 300 ms 
 */
void printOut() {

    lastPrint = millis();

    Serial.print("pitch: ");
    Serial.print(pos.pitch);

    Serial.print(" roll: ");
    Serial.print(pos.roll);
    
    Serial.print(" height: ");
    Serial.print(pos.height);
    
    Serial.print(" run x/sec");
    Serial.println(cycleCount);
    
}

void loop() {
    accel.read();
    gyro.read();
    mag.read();
    ping.read();
    
    pos.calculate(accel, gyro, mag, ping);
    
    if(millis() - lastCycle >= 1000 ){
        printOut();
        cycleCount = 0;
        lastCycle = millis();
    }
    cycleCount ++;
}

