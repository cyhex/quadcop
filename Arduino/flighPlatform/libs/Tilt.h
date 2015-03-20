/* 
 * File:   Tilt.h
 * Author: gx
 *
 * Created on March 20, 2015, 4:22 PM
 */

#ifndef TILT_H
#define	TILT_H

#include "ADXL345.h"
#include "L3G4200D.h"
#include "HMC5883.h"


class Tilt {
public:
    // tilt in degrees
    // x - 0 = balanced, -90 = nose up, 90 nose down
    // y - 0 balanced, -90 = left, 90 right (x nose direction)
    // z - not used
    typedef struct vector {
        float x, y, z;
    } vector;

    vector tilt;
    unsigned long lastTime;
    
    Tilt();
    void calculate(ADXL345::vector vectorAccel, L3G4200D::vector vectorGyro, 
    HMC5883::vector vectorMag);
private:

};

#endif	/* TILT_H */

