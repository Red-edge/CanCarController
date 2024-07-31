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

// using namespace std;
// using namespace chrono;
int systick = 0;

int main()
{
    // start = clock(); // clock()返回单位是毫秒
    while (1)
    {
        if (systick < int(clock()/ 1000))
        {
            systick++;
            printf("systick = %d \n", systick);
        }
    }

    return 0;
}