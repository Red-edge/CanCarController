/*

Name:           main
Version:        1.2.0
Date:           24.9.20
Developer:      Rededge
Desc:           main function for program

*/
#include "main.hpp"

int main()
{
    Systick tick;
    canTxProcessor canTx;
    canRxPreprocessor canRx;
    m2006Ctl m2006;

    heartbeat = 0;
    canRxflag = 0;
    tmplstick = tick.gettick();

    // int count = 0;

    char canname[8] = {};
    cout << "Init with current available can name : ";
    cin >> canname;

    canTx.init_canTx(canname, tick.gettick());
    canRx.Init_canRx(canname, tick.gettick());
    m2006.m2006Init(canRx.rx_frame);

    cout << "Align canTx clock at " << canTx.Lasttick << endl;
    cout << "Align canRx clock at " << canRx.Lasttick << endl;
    cout << "Align Systick clock at " << tick.errtick << endl;

    while (1)
    {
        uint64_t tmptick = tick.gettick();
        if ((tmptick - tmplstick) >= 500)
        {
            cout << "Heartbeat 500ms Count " << heartbeat << ". Lasted " << (tmptick - tmplstick) << endl;
            heartbeat++;
            can_frame tmp = m2006.m2006Update();
            memcpy(canTx.tx_tmp, tmp.data, 8);
            tmplstick = tmptick;
        }
        // Tx处理部
        if ((tmptick - canTx.Lasttick) >= tick.motorfrate)
        {
            canTx.canNTx(tmptick);
            // can_frame tmp = m2006.m2006Update();
            // memcpy(canTx.tx_tmp, tmp.data, 8);
            // m2006.m2006Update();
        }
        // Rx处理部
        if ((tmptick - canRx.Lasttick) >= 1)
        {
            canRxflag = canRx.reccheck(tmptick);
            if (canRxflag == 0)
            {
                cout << "Rx err ..." << endl;
            }
            // else if (canRxflag == 2)
            // {
            //     cout << "Rx 0x200, omit" << endl;
            // }
            // else if (canRxflag == 1)
            // {
            //     count++;
            //     cout << count << endl;
            // }
        }
    }

    return 0;
}
