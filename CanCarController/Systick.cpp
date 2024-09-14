/*

Name:           Systick
Version:        1.0.0
Date:           24.7.31
Developer:      Rededge
Desc:           Provide ms timetick from beginning of programme

*/

#include <iostream>
#include <ctime>
#include <unistd.h>
#include "Systick.hpp"

// using namespace std;
// using namespace chrono;
// int systick = 0;

int main()
{
    Systick systick;
    // start = clock(); // clock()返回单位是毫秒
    while (1)
    {
        if (systick.systick < int(clock()/ 1000))
        {
            systick.systick++;
            printf("systick = %d \n", systick.systick);
            systick.gettick();
        }
        
    }

    return 0;
}
