/* 
 * File:   PID.cpp
 * Author: gx
 * 
 * Created on March 19, 2015, 1:44 PM
 */

#include "PID.h"

PID::PID() {
}

void PID::setDefault() {
    p = 2.0;
    i = 0.0;
    d = 1.0;
    derivator = 0.0;
    integrator = 0.0;
    integratorMax = 500;
    integratorMin = -500;
}

void PID::setTarget(float target_val) {
    target = target_val;
    integrator = 0;
    derivator = 0;
}

float PID::update(float current_val) {
    error = target - current_val;
    float p_val = p * error;
    float d_val = d * (error - derivator);
    derivator = error;
    integrator = integrator + error;
    if (integrator > integratorMax) {
        integrator = integratorMax;
    }
    if (integrator < integratorMin) {
        integrator = integratorMin;
    }
    float i_val = integrator * i;

    float pid = p_val + i_val + d_val;
    return pid;
}
