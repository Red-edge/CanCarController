#ifndef CANRXPREPROCESSOR_HPP
#define CANRXPREPROCESSOR_HPP

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
#include "canTxProcessor.hpp"
#include "Systick.hpp"

using namespace std;

class canRxPreprocessor
{
private:
    /* data */
public:
    struct can_frame rx_frame[8] = {0};//canRx缓存
    struct can_frame rec_frame;
    int rxcheck;
    struct ifreq ifr;
    struct sockaddr_can can_addr;
    int ret;
    int sockfd;
    struct can_frame frame; // 定义一个 can_frame 变量
    int rxflag;
    int count_s;
    int count_f;
    int Lasttick;
    int reccheck(int64_t curtick);
    void Init_canRx(const char *canname, int64_t curtick);
    canRxPreprocessor(/* args */)
    {
        rxcheck = 0;
        ifr = {0};
        can_addr = {0};
        sockfd = -1;
        ret = 0;
        rxflag = 0;
        count_s = 0;
        count_f = 0;
        Lasttick = 0;
    }
    ~canRxPreprocessor()
    {
    }
};
// canRxPreprocessor canRx;

#endif