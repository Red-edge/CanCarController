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
#include "canRxPreprocessor.hpp"
#include "Systick.hpp"

using namespace std;

class canTxProcessor
{
private:
    /* data */
public:
    canTxProcessor(/* args */);
    ~canTxProcessor();
    int init_canTx();
    void canNTx();
    uint64_t Lasttick = 0;
};

canTxProcessor canTx;

canTxProcessor::canTxProcessor(/* args */)
{
}

canTxProcessor::~canTxProcessor()
{
}

// Systick sYstick;

#endif