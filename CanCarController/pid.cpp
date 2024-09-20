#include "pid.hpp"

using namespace std;

void pid::init_pid(float p, float i, float d, float max, float imax, int tgtspd)
{
    kp = p;
    ki = i;
    kd = d;
    this->max = max;
    this->imax = imax;
    this->tgtspd = tgtspd;
    pTmp = 0;
}

int pid::pidUpdate(int curspd)
{
    cout << curspd << " ";
    // if (curspd > 5000)
    //     curspd = ~curspd;
    this->curspd = curspd;
    pTmp = kp * (tgtspd - curspd);
    pTmp = (pTmp > max ? max : pTmp);
    pTmp = (pTmp < (-max) ? (-max) : pTmp);
    pTmp = pTmp + curspd;
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