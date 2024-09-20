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
    heartbeat = 0;
    canRxflag = 0;
    tmplstick = tick.gettick();

    char canname[8] = {};
    cout << "Init with current available can name : ";
    cin >> canname;

    canTx.init_canTx(canname, tick.gettick());
    canRx.Init_canRx(canname, tick.gettick());

    cout << "Align canTx clock at " << canTx.Lasttick << endl;
    cout << "Align canRx clock at " << canRx.Lasttick << endl;
    cout << "Align Systick clock at " << tick.errtick << endl;

    while (1)
    {
        uint64_t tmptick = tick.gettick();
        if ((tmptick - tmplstick) >= 200)
        {
            cout << "Heartbeat 200ms Count " << heartbeat << ". Lasted " << (tmptick - tmplstick) << endl;
            heartbeat++;
            tmplstick = tmptick;
        }
        // Tx处理部
        if ((tmptick - canTx.Lasttick) >= tick.motorfrate)
        {
            canTx.canNTx(tmptick);
        }
        // Rx处理部
        canRxflag = canRx.reccheck(tmptick);
        // if (canRxflag == 0)
        // {
        //     cout << "Rx err ..." << endl;
        // }
        // else if (canRxflag == 2)
        // {
        //     cout << "Rx 0x200, omit" << endl;
        // }
    }

    return 0;
}
