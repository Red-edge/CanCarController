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
    _tgtcur[4] = {0};
    m2006rxCan = m2006rx; // 将rx_frame的指针传递到电机初始化中，从而后续在使用时无需再复制内存

    m2006pid.init_pid(0.05f, 1.0f, 0.03f, 2000.0f, 500.0f, 1000);

    m2006txCan.can_dlc = 8;
    m2006txCan.can_id = 0x200;
    // memcpy(m2006txCan.data, m2006txTmp, 8);
}

void m2006Ctl::m2006Update()
{
    for (int i = 0; i < 4; i++)
    {
        // int curspd = int((m2006rxCan + i)->data[2]) * 16 * 16 + int((m2006rxCan + i)->data[3]);
        int16_t curspd = ((char)(m2006rxCan[i].data[2]) << 8) | (char)(m2006rxCan[i].data[3]);
        // cout << curspd << " ,";//观测用
        _tgtcur[i] = m2006pid.pidUpdate(curspd, i);
        // cout << _tgtcur[i] << ". "; // 观测用
        // memcpy(&m2006txTmp[2 * i + 1], (char *)(_tgtcur), 8);
        // memcpy(&m2006txTmp[2 * i], (char *)(_tgtcur >> 8), 8);
        // m2006txTmp[2 * i + 1] = (char)(_tgtcur);
        // m2006txTmp[2 * i] = (char)(_tgtcur >> 8);

        m2006txTmp[(2 * i)] = char(int16_t(_tgtcur[i] / (16 * 16)));            // 高八位
        m2006txTmp[(2 * i) + 1] = char(int16_t((abs(_tgtcur[i]) % (16 * 16)))); // 低八位

        // memcpy(&m2006txTmp[(2 * i)], (char *)(_tgtcur[i] / (16 * 16)), 1);            // 高八位
        // memcpy(&m2006txTmp[(2 * i) + 1], (char *)((abs(_tgtcur[i] % (16 * 16)))), 1); // 低八位

        // cout << _tgtcur << " ";
        // cout << endl;//观测用

        // 更新Tx
        memcpy(&m2006txCan.data[2 * i], &m2006txTmp[2 * i], 1);
        memcpy(&m2006txCan.data[(2 * i) + 1], &m2006txTmp[(2 * i) + 1], 1);
        // memcpy(&m2006txCan.data[2 * i], (m2006txTmp + 2 * i), 1);

        // 用于观测txCan内容
        // cout << int(m2006txCan.can_dlc) << endl;
        // cout << m2006txCan.can_id << endl;
        // for (int i = 0; i < 8; i++)
        // {

        //     cout << int(m2006txCan.data[i]) << " ";
        // }
        // cout << endl;
        // cout << endl;

        // for (int i = 0; i < 8; i++)
        // {
        //     for (int j = 0; j < 8; j++)
        //     {
        //         cout << int((m2006rxCan + i)->data[j]) << " ";
        //     }
        //     cout << endl;
        // }
        // }
        // cout << endl;

        // for (int i = 0; i < 8; i++)
        // {
        //     for (int j = 0; j < 8; j++)
        //     {
        //         cout << int((m2006rxCan + i)->data[j]) << " ";
        //     }
        //     cout << endl;
        // }

        // return m2006txCan;
    }
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
