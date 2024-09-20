#include "m2006Ctl.hpp"

void m2006Ctl::m2006Init(struct can_frame *m2006rx) // 用于重定位指针
{
    // m2006rxCan = m2006addr;
    // m2006rxCan.can_dlc = 8;
    // m2006rxCan.can_id = 0x200;
    // memcpy(m2006rxCan.data, m2006rxTmp, 8);
    m2006rxCan = m2006rx;

    m2006txCan.can_dlc = 8;
    m2006txCan.can_id = 0x200;
    memcpy(m2006txCan.data, m2006txTmp, 8);

    cout << int(m2006txCan.can_dlc) << endl;
    cout << m2006txCan.can_id << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << "0x" << int(m2006txCan.data[i]) << " ";
    }
    cout << endl;

    // pid注册
}

can_frame m2006Ctl::m2006Update()
{
    // rx传入pid,传出为tx
    //  for (int i = 0; i < 8; i++)
    //  {
    //      // 暂存Rx，更新pid后参数
    //  }

    // 测试tx更新
    int tmp = 0x08;
    if (m2006txTmp[1] >= 0x60)
    {
        tmp = -tmp;
    }
    else if (m2006txTmp[1] <= 0x10)
    {
        tmp = -tmp;
    }
    m2006txTmp[1] += tmp;

    // 更新Tx
    memcpy(m2006txCan.data, m2006txTmp, 8);

    // 用于观测txCan内容
    //  cout << int(m2006txCan.can_dlc) << endl;
    //  cout << m2006txCan.can_id << endl;
    //  for (int i = 0; i < 8; i++)
    //  {
    //      // for (int j = 0; j < 8; j++)
    //      // {
    //      cout << "0x" << int(m2006txCan.data[i]) << " ";
    //      // }
    //      // cout << endl;
    //  }
    // cout << endl;

    return m2006txCan;
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
