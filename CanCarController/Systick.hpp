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
    int64_t errtick;
    int64_t _errtick;
    int64_t gettick();
    void init_tick();
    int motorfrate;
    Systick()
    {
        errtick = 0;
        _errtick = 0;
        motorfrate = 1; 
        init_tick();
    }
    ~Systick()
    {
        cout << "Destructed current Systick" << endl;
    }
};

#endif
