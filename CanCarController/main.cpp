/*

Name:           main
Version:        1.3.0
Date:           24.9.24
Developer:      Rededge
Desc:           main function for program, 6 module uploaded

*/
#include "main.hpp"

using namespace std;

int main()
{
    Systick tick;
    canTxProcessor canTx;
    canRxPreprocessor canRx;
    m2006Ctl m2006;
    controller key;

    heartbeat = 0;
    canRxflag = 0;
    fcntlFlag = fcntl(STDIN_FILENO, F_GETFL, 0);
    tmplstick = tick.gettick();
    tmptick = tick.gettick();

    char canname[8] = {};
    cout << "Init with current available can name : ";
    cin >> canname;

    canTx.init_canTx(canname, tick.gettick());
    canRx.Init_canRx(canname, tick.gettick());
    m2006.m2006Init(canRx.rx_frame);
    key.init_Ctl(&m2006.m2006curpid.tgtspd, &tmptick);
    fcntl(STDIN_FILENO, F_SETFL, fcntlFlag | O_NONBLOCK);

    cout << "Align canTx clock at " << canTx.Lasttick << endl;
    cout << "Align canRx clock at " << canRx.Lasttick << endl;
    cout << "Align Systick clock at " << tick.errtick << endl;

    // sleep(2);
    while (1)
    {
        // a.detach();
        tmptick = tick.gettick();

        // Heartbeat心跳脉冲包，调试用
        if ((tmptick - tmplstick) >= 500)
        {
            cout << "Heartbeat 500ms Count " << heartbeat << ". Lasted " << (tmptick - tmplstick) << endl;
            heartbeat++;
            tmplstick = tmptick;
        }

        // Tx处理部
        if ((tmptick - canTx.Lasttick) >= tick.motorfrate)
        {
            key.spdCtl();
            m2006.m2006Update();
            memcpy(canTx.tx_tmp, m2006.m2006txCan.data, 8);
            canTx.canNTx(tmptick);
        }

        // Rx处理部
        if ((tmptick - canRx.Lasttick) >= 1)
        {
            canRxflag = canRx.reccheck(tmptick);
            switch (canRxflag)
            {
            case 0:
                cout << "Rx err ..." << endl;
                break;
            case 1:
            case 2:
                break;

            default:
                cout << "Unexpected Rx err ..." << endl;
                break;
            }
        }
        key.scanKeyboard();
    }

    return 0;
}
