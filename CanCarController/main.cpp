#include "main.hpp"


int main()
{
    Systick tick;
    canTxProcessor canTx;
    char canname[8] = {};
    cout << "Init with current available can name : ";
    cin >> canname;
    canTx.init_canTx(canname, tick.gettick());
    cout << "Align canTx clock at " << canTx.Lasttick << endl;
    cout << "Align Systick clock at " << tick.errtick << endl;
    while (1)
    {
        if ((tick.gettick() - canTx.Lasttick) >= tick.motorfrate)
        {
            canTx.txcheck = write(canTx.sockfd, &canTx.tx_frame, sizeof(canTx.tx_frame));
            if (canTx.txcheck == -1)
            {
                // std::cerr << "Failed to send CAN message" << std::endl;
                printf("%s\n", strerror(errno));
                // close(canTx.sockfd);
                // return 1;
                canTx.tx_frame.data[6] += 0x01;
            }
            else
            {
                // cout << "canTx success" << endl;
            }
            canTx.Lasttick = tick.gettick();
            // cout << "Inside success. Lasttick as " << Lasttick << endl;
        }
    }

    return 0;
}
