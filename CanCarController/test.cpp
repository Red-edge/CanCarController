#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "pid.hpp"
#include <termio.h>
#include <thread>

using namespace std;

float positionSet = 0.0f;
float speedSet = 0.0f;
float accelerationSet = 0.0f;
float currentSet = 0.0f;
char fdbx = 0x00;
char fdby = 0x00;
float kp(3.0f);
float ki(0.0f);
float kd(0.0f);
float maxOut(0.0f);
float maxIOut(0.0f);
float setv = 0.0f; // 速度需求值
int scan = 0;
int lastscan = 0;
int press = 0;

void scanKeyboard(int i) // 键盘输入读取
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
    int in;
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
    scan = in;
    exit;
}

char M2006Update(char x)
{
    float midp = 0;
    float midd = 0;
    char pidfdbx;
    midp = kp * (setv - int16_t(x));
    pidfdbx = char(midp + int16_t(x));
    return pidfdbx;
}

int main()
{
    int sockfd = -1;
    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (0 > socket(PF_CAN, SOCK_RAW, CAN_RAW))
    {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    struct ifreq ifr = {0};
    struct sockaddr_can can_addr = {0};
    int ret;

    strcpy(ifr.ifr_name, "can0"); // 指定名字
    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == -1)
    {
        std::cerr << "Failed to get CAN interface index" << std::endl;
        close(sockfd);
        return 1;
    }

    can_addr.can_family = AF_CAN; // 填充数据
    can_addr.can_ifindex = ifr.ifr_ifindex;

    /* 将套接字与 can0 进行绑定 */
    ret = bind(sockfd, (struct sockaddr *)&can_addr, sizeof(can_addr));
    if (0 > ret)
    {
        perror("bind error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    struct can_frame frame; // 定义一个 can_frame 变量
    struct can_frame rec_frame;

    int rec;

    frame.can_id = 0x200;
    frame.can_dlc = 8;
    frame.data[0] = fdbx;
    frame.data[1] = 0x00;
    frame.data[2] = fdby;
    frame.data[3] = 0x00;
    frame.data[4] = 0x00;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;

    // thread t(scanKeyboard, 1);
    // t.detach();

    while (1)
    {
        ret = write(sockfd, &frame, sizeof(frame)); // 发送数据
        if (ret == -1)                              // 如果 ret 不等于帧长度，就说明发送失败
            perror("write error");
        rec = read(sockfd, &rec_frame, sizeof(rec_frame));

        

        // printf("\n recv =  ");
        // for (int i = 0; i < rec_frame.can_dlc; ++i)
        // {
            // printf("0x%02X ", rec_frame.data[i]);
        // }
   
        /*
        // 键盘控制部分（需要手动编译 -lpthread）
        if (scan == 119)
        {
            setv = 10;
            press = 0;
            thread t(scanKeyboard, 1);
            t.detach();
            printf("scan= %d     case1 \n", scan);
        }
        else if (scan == 115)
        {
            setv = -10;
            press = 0;
            thread t(scanKeyboard, 1);
            t.detach();
            // printf("scan= %d     case2 \n", scan);
        }
        else if (scan != 0)
        {
            setv = 0;
            press = 0;
            thread t(scanKeyboard, 1);
            t.detach();
            // printf("scan= %d     case2.5 \n", scan);
        }
        press += 1;
        // printf("press = %d \n", press);
        if (press > 520)
        {
            if (scan == 0)
            {
                setv = 0;
                press = 0;
                // printf("scan= %d     case3\n", scan);
            }
            thread t(scanKeyboard, 1);
            t.detach();
        }
        scan = 0;
        */

        if (setv < -10)
        {
            setv = -10;
        }
        else if (setv > 10)
        {
            setv = 10;
        }

        frame.data[0] = M2006Update(rec_frame.data[2]);
        frame.data[2] = M2006Update(rec_frame.data[2]);
    }

    return 0;
}
