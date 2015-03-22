/* 
 * File:   HMC5883.h
 * Author: gx
 *
 * Created on March 20, 2015, 4:28 PM
 */

#ifndef HMC5883_H
#define	HMC5883_H

#define HMC5883_ADDRESS 0x1E //0011110b, I2C 7bit address of HMC5883

#define HMC5883_SCALE 1 //0.92


class HMC5883 {
public:
    // Magnetic field in milli guass
    typedef struct vector {
        float x, y, z;
    } vector;
    
    vector g;
    
    typedef struct callibration {
        float minx, miny, minz, maxx, maxy,maxz;
        float offsetx, offsety, offsetz;
        float scalex, scaley, scalez;
        
    } callibration;
    
    callibration c;
    
    HMC5883();
    void enableDefault(void);
    void read(void);
    void calibrate(void);
private:

};

#endif	/* HMC5883_H */

