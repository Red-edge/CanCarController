/*

Name:           m2006Ctl
Version:        1.1.0
Date:           24.9.24
Developer:      Rededge
Desc:           Process m2006 can msg and spd control, based on pid module, single current loop, dual loop tobedone

*/

#include "m2006Ctl.hpp"

using namespace std;

void m2006Ctl::m2006Init(struct can_frame *m2006rx) // 用于重定位指针
{
    memset(_tgtcur, 0, sizeof(_tgtcur));
    m2006rxCan = m2006rx; // 将rx_frame的指针传递到电机初始化中，从而后续在使用时无需再复制内存

    m2006curpid.init_pid(1.8f, 0.6f, 0.1f, 400.0f, 200.0f, 0.0f); // 电流环
    // m2006spdpid.init_pid(8.0f, 0.0f, 1.0f, 400.0f, 100.0f, 300.f);   // 电流环

    m2006txCan.can_dlc = 8;
    m2006txCan.can_id = 0x200;
    // memcpy(m2006txCan.data, m2006txTmp, 8);
}

void m2006Ctl::m2006Update()
{
    for (int j = 0; j < 4; j++)
    {

        int16_t curspd = ((char)(m2006rxCan[j].data[4]) << 8) | (char)(m2006rxCan[j].data[5]);
        _tgtcur[j] = m2006curpid.pidUpdate(curspd, j); // 电流环
        // _tgtcur[j] = m2006spdpid.pidUpdate(_tgtcur[j], j); // 电流环
        _tgtcur[j] = _tgtcur[j] * ((j % 2) ? -1 : 1);                 // 简易换向用，后续在Ctl里加变量判断
        m2006txTmp[(2 * j)] = (char)((int16_t)_tgtcur[j] >> 8);       // 提取高八位
        m2006txTmp[(2 * j) + 1] = (char)((int16_t)_tgtcur[j] & 0xFF); // 提取低八位


        // 更新Tx
        m2006txCan.data[2 * j] = m2006txTmp[2 * j];
        m2006txCan.data[2 * j + 1] = m2006txTmp[2 * j + 1];

    }
    // cout << endl;
}
