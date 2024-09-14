/*

Name:           Systick
Version:        1.1.0
Date:           24.9.14
Developer:      Rededge
Desc:           Provide ms timetick from beginning of programme; class declared; successed in connecting systick and canTxProcessor, failed to connect with canRx

*/

#include "Systick.hpp"
#include "canRxPreprocessor.hpp"

// using namespace std;
// using namespace chrono;
// int systick = 0;

// int main()  //Temp main for single file debug
// {
//     Systick sYstick;
//     sYstick.init_tick();
//     // start = clock(); // clock()返回单位是毫秒
//     while (1)
//     {
//         sYstick.gettick();
//         // sleep(1);
//     }

//     return 0;
// }
// Systick sYstick;

void Systick::init_tick()
{
    this->systick = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    // cout << "Init complete at clock " << this->systick.count() << endl;
}

uint64_t Systick::gettick()
{
    chrono::milliseconds systick;
    systick = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    // errtick = systick.count() - this->systick.count();
    // if ((errtick - _errtick)>=500)
    // {
    //     cout << "Get current running time " << errtick << endl;
    //     _errtick = errtick;
    // }

    return systick.count();
}
