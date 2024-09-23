/*

Name:           m2006Ctl
Version:        1.0.0
Date:           24.9.21
Developer:      Rededge
Desc:           Process m2006 can msg and spd control, based on pid module

*/

#include "m2006Ctl.hpp"

using namespace std;

void m2006Ctl::m2006Init(struct can_frame *m2006rx) // 用于重定位指针
{
    memset(_tgtcur, 0, sizeof(_tgtcur));
    m2006rxCan = m2006rx; // 将rx_frame的指针传递到电机初始化中，从而后续在使用时无需再复制内存

    m2006pid.init_pid(0.05f, 1.0f, 0.03f, 2000.0f, 500.0f, 1000);

    m2006txCan.can_dlc = 8;
    m2006txCan.can_id = 0x200;
    // memcpy(m2006txCan.data, m2006txTmp, 8);
}

void m2006Ctl::m2006Update()
{
    for (int j = 0; j < 4; j++)
    {
        int16_t curspd = ((char)(m2006rxCan[j].data[2]) << 8) | (char)(m2006rxCan[j].data[3]);
        _tgtcur[j] = m2006pid.pidUpdate(curspd, j);

        m2006txTmp[(2 * j)] = (char)((int16_t)_tgtcur[j] >> 8);       // 提取高八位
        m2006txTmp[(2 * j) + 1] = (char)((int16_t)_tgtcur[j] & 0xFF); // 提取低八位

        // cout << curspd << " ,";//观测用
        // cout << _tgtcur[i] << ". "; // 观测用
        // cout << endl;//观测用

        // 更新Tx
        m2006txCan.data[2 * j] = m2006txTmp[2 * j];
        m2006txCan.data[2 * j + 1] = m2006txTmp[2 * j + 1];

        // 用于观测txCan内容
        // cout << int(m2006txCan.can_dlc) << endl;
        // cout << m2006txCan.can_id << endl;
        // for (int i = 0; i < 8; i++)
        // {

        //     cout << int(m2006txCan.data[i]) << " ";
        // }
        // cout << endl;
    }
    // cout << endl;
}

// int main()
// {
//     m2006Ctl m2006;
//     struct can_frame tmp;
//     tmp.can_dlc = 8;
//     tmp.can_id = 0x200;
//     memcpy(tmp.data, m2006.m2006rxTmp, 8);
//     m2006.m2006Init(&tmp);
// }
