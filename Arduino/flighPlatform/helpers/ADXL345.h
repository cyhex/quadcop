/* 
 * File:   ADXL345.h
 * Author: gx
 *
 * Created on March 19, 2015, 7:35 PM
 */

#ifndef ADXL345_H
#define	ADXL345_H

#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

class ADXL345 {
public:
    typedef struct vector {
        float x, y, z;
    } vector;

    vector g;
    
    ADXL345();
    void enableDefault(void);
    void read(void);

};

#endif	/* ADXL345_H */

