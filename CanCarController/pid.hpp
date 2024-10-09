#ifndef PID_HPP
#define PID_HPP

#include <iostream>
#include <unistd.h>
#include <string.h>

class pid
{
private:
    /* data */
public:
    float kp;
    float ki;
    float kd;
    float max;
    float imax;
    float tgtspd; // rpm转子，出端RPM = /36
    float err[4][3];
    float dBuf[4];

    float pTmp;
    float iTmp[4];
    float dTmp;
    float Tmp;

    void init_pid(float p, float i, float d, float max, float imax, float tgtspd); // 可以用聚类判断电机，或者直接导入canRx, tgtspd单位是RPM
    int pidUpdate(float curspd, int i);

    pid(/* args */) {}
    ~pid() {}
};

// pid::pid(/* args */)
// {
// }

// pid::~pid()
// {
// }

#endif