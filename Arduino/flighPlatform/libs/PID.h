/* 
 * File:   PID.h
 * Author: gx
 *
 * Created on March 19, 2015, 1:44 PM
 */

#ifndef PID_H
#define	PID_H

class PID {
public:
    float p;
    float i;
    float d;
    float derivator;
    float integrator;
    float integratorMax;
    float integratorMin;
    float target;
    float error;
    
    
    PID();
    void setDefault();
    void setTarget(float target_val);
    float update(float current_val);
};

#endif	/* PID_H */

