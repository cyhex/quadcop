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
    typedef struct vector {
        float x, y, z;
    } vector;

    vector tilt;
    int heading;
    
    Tilt();
    void calculate(ADXL345::vector vectorAccel, L3G4200D::vector vectorGyro, 
    HMC5883::vector vectorMag);
private:

};

#endif	/* TILT_H */

