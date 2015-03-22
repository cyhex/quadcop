/* 
 * File:   Postion.h
 * Author: gx
 *
 * Created on March 21, 2015, 6:50 AM
 */

#ifndef POSTION_H
#define	POSTION_H

#include "ADXL345.h"
#include "L3G4200D.h"
#include "HMC5883.h"
#include "HCSRC04.h"

#define POSITION_GYR_RATIO 0.5

class Postion {
public:
    //Degrees: 0 = balanced, -90 = nose up, 90 nose down
    float pitch;
    //Degrees: 0 = balanced, -90 = left, 90 right (x nose direction)
    float roll;
    //Degrees: 0 = North (x nose direction)
    float heading;
    // distance to ground in CM
    double height;
    
    unsigned long lastTime;

    Postion();
    void calculate(ADXL345 acc, L3G4200D gyro, HMC5883 mag, HCSRC04 ping);
};


#endif	/* POSTION_H */

