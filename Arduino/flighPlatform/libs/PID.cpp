/* 
 * File:   PID.cpp
 * Author: gx
 * 
 * Created on March 19, 2015, 1:44 PM
 */

#include "PID.h"

PID::PID() {
}

float PID::run(float newPoint, float currentPoint){
    p = newPoint * Kp;
    d = (newPoint - currentPoint) * Kd;
    i = i + (newPoint * Ki);
    return p + i + d;
}
