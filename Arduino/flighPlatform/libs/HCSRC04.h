/* 
 * File:   HCSRC04.h
 * Author: gx
 *
 * Created on March 22, 2015, 12:28 PM
 */

#ifndef HCSRC04_H
#define	HCSRC04_H

#define HCSRC04_PIN_TIG 3
#define HCSRC04_PIN_ECHO 4
#define HCSRC04_PING_TIME 500 // in ms

class HCSRC04 {
public:
    // in cm
    float distance; 
    unsigned long lastRead;
    HCSRC04();
    void enableDefault(void);
    void read(void);
};

#endif	/* HCSRC04_H */

