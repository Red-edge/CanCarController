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
    iTmp[4] = {0};
    dTmp = 0;
    Tmp = 0;
    err[4][2] = {0};
    dBuf[4][2] = {0};
}

int pid::pidUpdate(int16_t curspd, int i)
{
    // 速度反馈转电流输出，相当于将速度的差值映射到电流的调教
    // if (curspd >)
    // {

    // }

    // this->curcur = curspd;
    pTmp = 0;
    dTmp = 0;
    Tmp = 0;

    err[i][2] = err[i][1];
    err[i][1] = err[i][0];
    err[i][0] = tgtspd - curspd;

    dBuf[i][2] = dBuf[i][1];
    dBuf[i][1] = dBuf[i][0];
    dBuf[i][0] = (err[i][0] - 2.0f * err[i][1] + err[i][2]);

    // kp实现
    pTmp = kp * err[i][0];
    iTmp[i] += err[i][0];
    dTmp = kd * dBuf[i][0];

    iTmp[i] = (iTmp[i] > imax ? imax : iTmp[i]);
    iTmp[i] = (iTmp[i] < (-imax) ? (-imax) : iTmp[i]);

    Tmp = pTmp + dTmp + iTmp[i];
    // Tmp = Tmp * 10;

    Tmp = (Tmp > max ? max : Tmp);
    Tmp = (Tmp < (-max) ? (-max) : Tmp);
    // pTmp = pTmp * 10.0f;
    // cout << curspd << ", ";
    // cout << pTmp << " ";
    // cout << dTmp << " ";
    // cout << Tmp << endl;
    // curcut += pTmp;
    return Tmp;
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