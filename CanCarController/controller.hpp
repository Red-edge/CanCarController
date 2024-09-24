#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <iostream>
#include <termio.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

class controller
{
private:
    /* data */
public:
    int in;
    float *m2006spd;
    uint64_t *curtick;
    uint64_t keyFlagTime[16]; // 可用于存储16个键位的按下状态，拟用于同时按下两键的需求
    struct termios new_settings;
    struct termios stored_settings;

    void init_Ctl(float *tgtspd, uint64_t *curtick);
    void spdCtl();
    int scanKeyboard();
    int setKeyFlag();
    controller(/* args */)
    {
        in = 0;
    }
    ~controller() {}
};

// controller::controller(/* args */)
// {
// }

// controller::~controller()
// {
// }

#endif
