/*

Name:           CanRxPreprocessor
Version:        1.1.0
Date:           24.9.14
Developer:      Rededge
Desc:           Process the CAN RX and store them in cache; classes added, failed to connect

*/
#include "canRxPreprocessor.hpp"

int canRxPreprocessor::reccheck(uint64_t curtick)
{

    rxflag = 0;
    rxcheck = read(sockfd, &rec_frame, sizeof(rec_frame)); // read怎么写的？是读取的can网络设备还是can信号情况？为什么信号会一直有？
    if (rxcheck > 0)
    {
        Lasttick = curtick;
        if (rec_frame.can_id == 0x200)
        {
            return 2;
        }

        for (int i = 0; i < 8; i += 1)
        {
            if (rec_frame.can_id == 0x201 + i)
            {
                rx_frame[i] = rec_frame;
                // printf("Receive can sig from can 0x%02x. \n", rec_frame.can_id);
                // cout << "Rx Can Succ." << endl;
                rxflag = 1;
            }
        }
        if (rxflag == 0)
        {
            cout << "Rx Can Unknown." << endl;
        }

        return 1;
    }
    else
    {
        Lasttick = curtick;
        return 0;
    }

    return 0;
}

void canRxPreprocessor::Init_canRx(const char *canname, uint64_t curtick)
{

    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (0 > socket(PF_CAN, SOCK_RAW, CAN_RAW))
    {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    strcpy(ifr.ifr_name, canname); // 指定名字，注意改掉名字

    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == -1)
    {
        std::cerr << "Failed to get CAN interface index" << std::endl;
        printf("%s\n", strerror(errno));
        close(sockfd);
        // return 1;
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

    Lasttick = curtick;
}
