#ifndef CANTXPROCESSOR_HPP
#define CANTXPROCESSOR_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <termio.h>
#include <thread>
#include <errno.h>
#include "Systick.hpp"

using namespace std;

class canTxProcessor
{
private:
    /* data */
public:
    int txcheck;
    struct ifreq ifr = {0};
    struct sockaddr_can can_addr = {0};
    int ret;
    int sockfd = -1;
    struct can_frame tx_frame;
    unsigned char tx_tmp[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    int txflag = 0;
    int count_s = 0;
    int count_f = 0;
    uint64_t Lasttick;
    canTxProcessor(/* args */)
    {
        Lasttick = 0;
    }
    ~canTxProcessor()
    {
        cout << "Destructed current canTxProcessor" << endl;
    }

    void canNTx(uint64_t curtick);
    void init_canTx(const char *canname, uint64_t curtick);
};

// canTxProcessor canTx;

// Systick sYstick;

#endif