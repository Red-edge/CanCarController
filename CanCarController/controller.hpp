#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <iostream>
#include <termio.h>
#include <stdio.h>
#include <unistd.h>


class controller
{
private:
    /* data */
public:
    int in;

    int scanKeyboard();
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
