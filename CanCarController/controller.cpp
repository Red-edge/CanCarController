/*

Program:        CanCarControllers
Name:           controller
Version:        1.0.0
Date:           24.9.21
Developer:      Rededge
Desc:           For rc input and output process.

*/

#include "controller.hpp"

using namespace std;

void controller::init_Ctl(float *tgtspd, int64_t *curtick)
{
    in = 0;
    m2006spd = tgtspd;
    this->curtick = curtick;
    memset(keyFlagTime, 0, sizeof(keyFlagTime));
}

int controller::scanKeyboard()
{
    //  struct termios
    //    {
    //      tcflag_t c_iflag;		/* input mode flags */
    //      tcflag_t c_oflag;		/* output mode flags */
    //      tcflag_t c_cflag;		/* control mode flags */
    //      tcflag_t c_lflag;		/* local mode flags */
    //      cc_t c_line;			/* line discipline */
    //      cc_t c_cc[NCCS];		/* control characters */
    //      speed_t c_ispeed;		/* input speed */
    //      speed_t c_ospeed;		/* output speed */
    //  #define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
    //  #define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
    //    };

    tcgetattr(STDIN_FILENO, &stored_settings); // 获得stdin 输入
    new_settings = stored_settings;            //
    new_settings.c_lflag &= (~ICANON);         //
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(STDIN_FILENO, &stored_settings); // 获得stdin 输入
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings); //

    in = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &stored_settings);

    setKeyFlag();
    return in;
}

int controller::setKeyFlag()
{
    switch (in)
    {
    case 119: // w or W pressed
    case 87:
        memcpy(&keyFlagTime[0], curtick, sizeof(int64_t));
        // cout << "W pressed " << keyFlagTime[0] << endl;
        break;
    case 115: // s or S pressed
    case 83:
        memcpy(&keyFlagTime[1], curtick, sizeof(int64_t));
        // cout << "S pressed " << keyFlagTime[1] << endl;
        break;
        break;
    case 97: // a or A pressed
    case 67:
        memcpy(&keyFlagTime[2], curtick, sizeof(int64_t));
        break;
    case 100: // d or D pressed
    case 68:
        memcpy(&keyFlagTime[3], curtick, sizeof(int64_t));
        break;
    default:
        break;
    }
    return 0;
}

void controller::spdCtl()
{

    // if ((*curtick - keyFlagTime[0]) <= 500)
    // {
    //     *m2006spd = 300;
    //     return;
    // }
    // if ((*curtick - keyFlagTime[1]) <= 500)
    // {
    //     *m2006spd = -300;
    //     return;
    // }   
    // // cout << *m2006spd << endl;
    // // *m2006spd = 0;
    // return;
}

// int main(int argc, char *argv[])
// {

//     while (1)
//     {
//         // printf(":%d\r\n", scanKeyboard());
//         scanKeyboard();
//         //    int input_id = scanKeyboard();
//         //    switch(input_id) {
//         //      case 119:  //w or can set as case 'w':
//         //      case 87:   //W case 'W':
//         //        break;
//         //      case 115: //s
//         //      case 83:  //S
//         //        break;
//         //      case 97:  //a
//         //      case 67:  //A
//         //        break;
//         //      case 100: //d
//         //      case 68:  //D
//         //        break;
//         //      default:
//         //        break;
//         //    }
//     }
// }
