#ifndef PID_H
#define	PID_H

#define PID_Ki 0.39 // 0.39 analogRead(A0)
#define PID_Kp 19 // 19.8 analogRead(A1)
#define PID_Kd 44 //44 analogRead(A2)

class PID {
public:
    float p;
    float i;
    float d;
    float Kp;
    float Kd;
    float Ki;
    float run(float newPoint, float currentPoint);
};

#endif	/* PID_H */

