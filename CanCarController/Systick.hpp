#ifndef SYSTICK_HPP
#define SYSTICK_HPP

#include <iostream>
#include <chrono>
#include <unistd.h>
#include "canRxPreprocessor.hpp"
#include "canTxProcessor.hpp"

using namespace std;
using namespace chrono;

class Systick
{
private:
    std::chrono::milliseconds systick;

public:
    uint64_t errtick = 0;
    uint64_t _errtick = 0;
    uint64_t gettick();
    void init_tick();
    int motorfrate = 1;
};

// Systick sYstick;

#endif
