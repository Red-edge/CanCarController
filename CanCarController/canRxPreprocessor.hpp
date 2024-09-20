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
    canRxPreprocessor(/* args */);
    ~canRxPreprocessor();
    struct can_frame rx_frame[8] = {0};
    int reccheck();
    struct can_frame rec_frame;
};
// canRxPreprocessor canRx;


canRxPreprocessor::canRxPreprocessor(/* args */)
{
}

canRxPreprocessor::~canRxPreprocessor()
{
}







#endif