#include "PID.h"

float PID::run(float newPoint, float currentPoint) {
    p = newPoint * Kp;
    d = (newPoint - currentPoint) * Kd;
    i = i + (newPoint * Ki);
    return p + i + d;
}