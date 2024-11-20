/*

Program:        CanCarController
Name:           m2006Ctl
Version:        1.1.0
Date:           24.9.24
Developer:      Rededge
Desc:           Process m2006 can msg and spd control, based on pid module, single current loop, dual loop tobedone, using UTF-8 coding

*/

#include "m2006Ctl.hpp"

using namespace std;

void m2006Ctl::m2006Init(struct can_frame *m2006rx) // 用于重定位指针
{
    memset(_tgtcur, 0, sizeof(_tgtcur));
    m2006rxCan = m2006rx; // 将rx_frame的指针传递到电机初始化中，从而后续在使用时无需再复制内存

    m2006spdpid.init_pid(1.0f, 0.0f, 1.0f, 1000.0f, 200.0f, 0.0f); // 速度环
    m2006balpid.init_pid(1.0f, 0.03f, 0.0f, 200.0f, 200.0f, 0.0f); // 平衡环

    m2006txCan.can_dlc = 8;
    m2006txCan.can_id = 0x200;

    mpuLife = mpu.initialize();
    // memcpy(m2006txCan.data, m2006txTmp, 8);
}

void m2006Ctl::m2006Update()
{
    if (mpuLife != 0)
    {
        mpu.readAccelerometer(gx, gy, gz);
    }

    // cout << gx << " " << gy << " " << gz << endl;
    for (int j = 0; j < 4; j++)
    {
        // m2006spdpid.init_pid(0.85f, 0.01f, 1.0f, 1000.0f, 200.0f, m2006curpid.tgtspd[j]);

        // m2006balpid.tgtspd[j] += 0.01;

        curspd = ((uint16_t)(m2006rxCan[j].data[2]) << 8) | (uint16_t)(m2006rxCan[j].data[3]);
        curspd = curspd / 36;
        // _tgtcur[j] = int16_t(m2006spdpid.pidUpdate(m2006spdpid.tgtspd[j] - curspd, j)); // 速度环

        // _tgtcur[j] = m2006balpid.pidUpdate(gx / 10 - _tgtcur[j], j); // 这里应该是用速度环输出的电流（加速度）与角度（重力分量导致的加速度）做差得到一个目标角度
        _tgtcur[j] = m2006spdpid.pidUpdate(m2006spdpid.tgtspd[j] - curspd, j);
        // _tgtcur[j] = _tgtcur[j] * ((j % 2) ? -1 : 1);                 // 简易换向用，后续在Ctl里加变量判断
        m2006txTmp[(2 * j)] = (unsigned char)((uint16_t)_tgtcur[j] >> 8);       // 提取高八位
        m2006txTmp[(2 * j) + 1] = (unsigned char)((uint16_t)_tgtcur[j] & 0xFF); // 提取低八位

        // 更新Tx
        m2006txCan.data[2 * j] = m2006txTmp[2 * j];
        m2006txCan.data[2 * j + 1] = m2006txTmp[2 * j + 1];

        // if (j == 0)
        // {
        //     // cout << _tgtcur[j] << endl;
        //     int16_t tmpTx = (((uint16_t)(m2006txTmp[(2 * j)]) << 8) | (uint16_t)(m2006txTmp[(2 * j) + 1]));
        //     // printf("%d, %d \n", (uint16_t)m2006txTmp[(2 * j)], (uint16_t)m2006txTmp[(2 * j) + 1]);
        //     cout << tmpTx << ", " << curspd << endl;
        // }
    }

    // cout << m2006curpid.tgtspd << endl;
}
