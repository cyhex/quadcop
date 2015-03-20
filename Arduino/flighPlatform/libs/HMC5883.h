/* 
 * File:   HMC5883.h
 * Author: gx
 *
 * Created on March 20, 2015, 4:28 PM
 */

#ifndef HMC5883_H
#define	HMC5883_H

#define HMC5883_ADDRESS 0x1E //0011110b, I2C 7bit address of HMC5883

class HMC5883 {
public:
    // heading in Radians
    typedef struct vector {
        float x, y, z;
    } vector;

    vector g;
    
    HMC5883();
    void enableDefault(void);
    void read(void);
private:

};

#endif	/* HMC5883_H */

