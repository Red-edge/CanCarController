#ifndef SYSTICK_HPP
#define SYSTICK_HPP

#include <iostream>
#include <chrono>
#include <unistd.h>
#include "canTxProcessor.hpp"

using namespace std;
using namespace chrono;

class Systick
{
private:
    std::chrono::milliseconds systick;

public:
    uint64_t errtick;
    uint64_t _errtick;
    uint64_t gettick();
    void init_tick();
    int motorfrate;
    Systick()
    {
        errtick = 0;
        _errtick = 0;
        motorfrate = 1; // 别太块！电流高频波动可能损坏电机！！！
        init_tick();
    }
    ~Systick()
    {
        cout << "Destructed current Systick" << endl;
    }
};

#endif
