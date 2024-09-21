#include "pid.hpp"

using namespace std;

void pid::init_pid(float p, float i, float d, float max, float imax, float tgtspd)
{
    kp = p;
    ki = i;
    kd = d;
    this->max = max;
    this->imax = imax;
    this->tgtspd = tgtspd;
    pTmp = 0;
}

int pid::pidUpdate(int16_t curcut)
{
    // 速度反馈转电流输出，相当于将速度的差值映射到电流的调教
    // if (curspd >)
    // {

    // }

    // this->curcur = curspd;
    pTmp = kp * float(tgtspd - curcut);
    pTmp = (pTmp > max ? max : pTmp);
    pTmp = (pTmp < (-max) ? (-max) : pTmp);
    // pTmp = pTmp * 10.0f;
    // cout << pTmp << endl;
    // curcut += pTmp;
    return pTmp;
}

// int main()
// {
//     pid PID;
//     PID.init_pid(0.5, 0, 0, 100, 0, 100);
//     int cur = 10;
//     while (1)
//     {
//         sleep(1);
//         cur = PID.pidUpdate(cur);
//         cout << cur << endl;
//     }
// }