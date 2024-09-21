/*

Name:           controller
Version:        1.0.0
Date:           24.9.21
Developer:      Rededge
Desc:           For rc input and output process.

*/

#include "controller.hpp"

using namespace std;

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
    
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(STDIN_FILENO, &stored_settings); // 获得stdin 输入
    new_settings = stored_settings;            //
    new_settings.c_lflag &= (~ICANON);         //
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(STDIN_FILENO, &stored_settings); // 获得stdin 输入
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings); //

    in = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &stored_settings);
    return in;
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
