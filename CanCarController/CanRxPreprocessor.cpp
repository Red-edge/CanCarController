/*

Name:           CanRxPreprocessor
Version:        1.0.0
Date:           24.7.31
Developer:      Rededge

*/

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

int rxcheck;
int reccheck();
struct ifreq ifr = {0};
struct sockaddr_can can_addr = {0};
int ret;
int sockfd = -1;
struct can_frame frame; // 定义一个 can_frame 变量
struct can_frame rec_frame;
struct can_frame rx_frame[8] = {0};
int rxflag = 0;
int count_s = 0;
int count_f = 0;

int main()
{

    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (0 > socket(PF_CAN, SOCK_RAW, CAN_RAW))
    {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    strcpy(ifr.ifr_name, "vcan0"); // 指定名字

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

    while (1)
    {
        if (reccheck() == 1)
        {
            for (int i = 0; i < 8; i += 1)
            {
                if (rec_frame.can_id == 0x201 + i)
                {
                    count_s++;
                    printf("Receive can sig from can 0x%02x. Count %d. \n", rec_frame.can_id, count_s);
                    rx_frame[i] = rec_frame;
                    rxflag = 1;
                }
            }
        }
        if (rxflag == 0)
        {
            printf("Rx can msg from unknown device. Count %d. \n", count_f);
            count_f++;
        }
        rxflag = 0;
        printf("Current cached can signal \n");

        for (int i = 0; i < 8; i += 1)
        {
            printf("rx_frame[%d]=   ", i);
            for (int j = 0; j < rec_frame.can_dlc; ++j)
            {
                printf("0x%02X ", rx_frame[i].data[j]);
            }
            printf("\n");
        }
    }
}

int reccheck()
{
    rxcheck = read(sockfd, &rec_frame, sizeof(rec_frame)); // read怎么写的？是读取的can网络设备还是can信号情况？为什么信号会一直有？
    if (rxcheck > 0)
    {
        printf("Rx Can Succ.\n");
        return 1;
    }
    else
    {
        printf("Rx Can Err.\n");
        return 0;
    }
}