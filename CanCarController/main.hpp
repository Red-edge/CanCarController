#ifndef MAIN_HPP
#define MAIN_HPP

#include "canRxPreprocessor.hpp"
#include "canTxProcessor.hpp"
#include "Systick.hpp"
#include "m2006Ctl.hpp"
#include "pid.hpp"
#include "controller.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int heartbeat;
int canRxflag;
int fcntlFlag;
int64_t tmptick;
int64_t tmplstick; // 启动时间
std::thread::id threadid;
char canname[8] = {};

#endif