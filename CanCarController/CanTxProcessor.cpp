/*

Name:           CanTxProcessor
Version:        1.0.0
Date:           24.7.31
Developer:      Rededge
Desc:           Process the CAN RX and store them in cache

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
#include <termio.h>
#include <thread>
#include <errno.h>
#include "Systick.hpp"

int txcheck;
struct ifreq ifr = {0};
struct sockaddr_can can_addr = {0};
int ret;
int sockfd = -1;
struct can_frame tx_frame;
char tx_tmp[8] = {0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
int txflag = 0;
int count_s = 0;
int count_f = 0;
int Lasttick = 0;

int main()
{

    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (0 > socket(PF_CAN, SOCK_RAW, CAN_RAW))
    {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    strcpy(ifr.ifr_name, "can0"); // 指定名字，注意改掉名字

    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == -1)
    {
        std::cerr << "Failed to get CAN interface index" << std::endl;
        printf("%s\n", strerror(errno));
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

    // 准备Can信号，这里先只考虑2006电机了
    std::memset(&tx_frame, 0, sizeof(tx_frame));
    tx_frame.can_id = 0x200; // 设置 CAN ID
    tx_frame.can_dlc = 8;    // 设置数据长度为 8 字节
    std::memcpy(tx_frame.data, tx_tmp, 8);

    can_addr.can_family = AF_CAN; // 填充数据
    can_addr.can_ifindex = ifr.ifr_ifindex;

    Lasttick = Systick::gettick();

    while (1)
    {
        if (Systick::gettick() != Lasttick)
        {
            txcheck = write(sockfd, &tx_frame, sizeof(tx_frame));
            if (txcheck == -1)
            {
                std::cerr << "Failed to send CAN message" << std::endl;
                printf("%s\n", strerror(errno));
                close(sockfd);
                return 1;
            }
            Lasttick = Systick::gettick();
        }
    }
}
