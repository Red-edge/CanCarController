#ifndef M2006CTL_HPP
#define M2006CTL_HPP

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
#include "pid.hpp"

using namespace std;

class m2006Ctl
{
private:
    /* data */
public:
    void m2006Init(struct can_frame *m2006rx);
    can_frame m2006Update();
    pid m2006pid;
    struct can_frame *m2006rxCan; // for 2006 rx tmp store and process from rx_frame
    struct can_frame m2006txCan;  // for 2006 tx tmp store and process to tx_frame
    char m2006rxTmp[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char m2006txTmp[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    m2006Ctl(/* args */)
    {
    }
    ~m2006Ctl() {}
};

// m2006Ctl::m2006Ctl(/* args */)
// {
// }

// m2006Ctl::~m2006Ctl()
// {
// }

#endif