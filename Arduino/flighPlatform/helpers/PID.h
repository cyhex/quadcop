/* 
 * File:   PID.h
 * Author: gx
 *
 * Created on March 19, 2015, 1:44 PM
 */

#ifndef PID_H
#define	PID_H

#define PIDx_Ki 0.39 // 0.39 analogRead(A0)
#define PIDx_Kp 19 // 19.8 analogRead(A1)
#define PIDx_Kd 44 //44 analogRead(A2)

class PID {
public:
    float p;
    float i;
    float d;
    float Kp;
    float Kd;
    float Ki;
    
    PID();
    float run(float newPoint, float currentPoint);
};

#endif	/* PID_H */

