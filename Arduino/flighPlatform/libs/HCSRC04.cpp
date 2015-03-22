/* 
 * File:   HCSRC04.cpp
 * Author: gx
 * 
 * Created on March 22, 2015, 12:28 PM
 */

#include <Arduino.h>

#include "HCSRC04.h"

HCSRC04::HCSRC04() {
}

void HCSRC04::enableDefault() {
    pinMode(HCSRC04_PIN_TIG, OUTPUT);
    pinMode(HCSRC04_PIN_ECHO, INPUT);
    lastRead = 0;
}

void HCSRC04::read() {

    if (millis() - lastRead > HCSRC04_PING_TIME) {
        lastRead = millis();
        // trigger ping
        digitalWrite(HCSRC04_PIN_TIG, LOW);
        delayMicroseconds(2);
        digitalWrite(HCSRC04_PIN_TIG, HIGH);
        delayMicroseconds(5);
        digitalWrite(HCSRC04_PIN_TIG, LOW);

        // read time 
        float t = pulseIn(HCSRC04_PIN_ECHO, HIGH, 232000);
        // The speed of sound is 340 m/s or 29 microseconds per centimeter.
        distance = t / 29.0 / 2.0;
    }


}
