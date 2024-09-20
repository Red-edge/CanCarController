#ifndef PID_HPP
#define PID_HPP

#include <iostream>
#include <unistd.h>


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
    int curspd;
    int tgtspd;

    int pTmp;

    void init_pid(float p, float i, float d, float max, float imax, int tgtspd); // 可以用聚类判断电机，或者直接导入canRx
    int pidUpdate(int curspd);

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