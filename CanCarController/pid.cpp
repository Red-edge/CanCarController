/*

Program:        CanCarController
Name:           pid
Version:        1.0.0
Date:           24.10.9
Developer:      Rededge
Desc:           pid calculation module

*/

#include "pid.hpp"

using namespace std;

void pid::init_pid(float p, float i, float d, float max, float imax, float tgtspd)
{
    kp = p;
    ki = i;
    kd = d;
    this->max = max;
    this->imax = imax;
    for (int i = 0; i < 4; i++)
    {
        this->tgtspd[i] = tgtspd;
    }

    pTmp = 0;
    memset(iTmp, 0, sizeof(iTmp));
    dTmp = 0;
    Tmp = 0;
    memset(err, 0, sizeof(err));
    memset(dBuf, 0, sizeof(dBuf));
}

int pid::pidUpdate(float curspd, int i)
{
    // 累值传递
    err[i][2] = err[i][1];
    err[i][1] = err[i][0];
    err[i][0] = tgtspd[i] - curspd;

    dBuf[i] = (err[i][0] - 2.0f * err[i][1] + err[i][2]);

    // pid实现
    pTmp = kp * err[i][0];
    iTmp[i] += ki * err[i][0];
    dTmp = kd * dBuf[i];

    iTmp[i] = (iTmp[i] > imax ? imax : iTmp[i]);
    iTmp[i] = (iTmp[i] < (-imax) ? (-imax) : iTmp[i]);

    Tmp = pTmp + dTmp + iTmp[i];

    Tmp = (Tmp > max ? max : Tmp);
    Tmp = (Tmp < (-max) ? (-max) : Tmp);
    Tmp = Tmp;

    // pid值反馈可视化
    // cout << i << ", ";
    // cout << err[i][0] << " ";
    // cout << err[i][1] << " ";
    // cout << err[i][2] << ",  ";

    // cout << dBuf[i] << " ";
    // cout << dBuf[i] << " ";
    // cout << dBuf[i] << " ";

    return Tmp;
}

// void pid::set_tgt_spd(float tgtspd, int i)
// {
//     init_pid(kp, ki, kd, max, imax, tgtspd);
// }

// int main()//测试使用
// {
//     pid PID;
//     PID.init_pid(0.5, 0.4, 0.008, 1000, 500, 200);
//     int cur = 10;
//     while (1)
//     {
//         sleep(1);
//         cur = PID.pidUpdate(cur, 0);
//         cout << cur << " ";
//         cur = PID.pidUpdate(cur, 0);
//         cout << cur << " ";
//         cur = PID.pidUpdate(cur, 0);
//         cout << cur << " ";
//         cur = PID.pidUpdate(cur, 0);
//         cout << cur << " ";
//         cur = PID.pidUpdate(cur, 0);
//         cout << cur << endl;
//     }
// }