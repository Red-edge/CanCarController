/*

Name:           Systick
Version:        1.1.0
Date:           24.9.14
Developer:      Rededge
Desc:           Provide ms timetick from beginning of programme; class declared; successed in connecting systick and canTxProcessor, failed to connect with canRx

*/

#include "Systick.hpp"

void Systick::init_tick()
{
    systick = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    // cout << "Init complete at clock " << this->systick.count() << endl;
}

uint64_t Systick::gettick()
{
    chrono::milliseconds curtick;
    curtick = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    errtick = curtick.count() - systick.count();
    // if ((errtick - _errtick) >= 500)
    // {
    //     cout << "Get current running time " << errtick << endl;
    //     _errtick = errtick;
        
    // }
    // Systick::~Systick();
    return errtick;
}


// int main()
// {
//     Systick tick;

//     while (1)
//     {
//         tick.gettick();
//     }

//     return 0;
// }