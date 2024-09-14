/*

Name:           CanRxPreprocessor
Version:        1.1.0
Date:           24.9.14
Developer:      Rededge
Desc:           Process the CAN RX and store them in cache; classes added, failed to connect

*/
#include "canRxPreprocessor.hpp"

int rxcheck;
struct ifreq ifr = {0};
struct sockaddr_can can_addr = {0};
int ret;
int sockfd = -1;
struct can_frame frame; // 定义一个 can_frame 变量
int rxflag = 0;
int count_s = 0;
int count_f = 0;
int Lasttick = 0;
canRxPreprocessor canRx;

int canRxPreprocessor::reccheck()
{
    rxcheck = read(sockfd, &rec_frame, sizeof(rec_frame)); // read怎么写的？是读取的can网络设备还是can信号情况？为什么信号会一直有？
    if (rxcheck > 0)
    {
        cout << "Rx Can Succ." << endl;
        return 1;
    }
    else
    {
        cout << "Rx Can Err." << endl;
        return 0;
    }
}

int main()
{

    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (0 > socket(PF_CAN, SOCK_RAW, CAN_RAW))
    {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    strcpy(ifr.ifr_name, "vcan"); // 指定名字，注意改掉名字

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

    canTx.init_canTx();
    sYstick.init_tick();
    Lasttick = sYstick.gettick();

    while (1)
    {
        if ((sYstick.gettick() - Lasttick) >= sYstick.motorfrate)
        {
            canTx.canNTx();
        }
        if (canRx.reccheck() == 1)
        {
            for (int i = 0; i < 8; i += 1)
            {
                if (canRx.rec_frame.can_id == 0x201 + i)
                {
                    count_s++;
                    printf("Receive can sig from can 0x%02x. Count %d. \n", canRx.rec_frame.can_id, count_s);
                    canRx.rx_frame[i] = canRx.rec_frame;
                    rxflag = 1;
                }
            }
        }
        if (rxflag == 0)
        {
            printf("Rx Can msg from unknown device. Count %d. \n", count_f);
            count_f++;
        }
        rxflag = 0;
        printf("Current cached can signal \n");

        // RX cache display
        for (int i = 0; i < 8; i += 1)
        {
            printf("rx_frame[%d]=   ", i);
            for (int j = 0; j < canRx.rec_frame.can_dlc; ++j)
            {
                printf("0x%02X ", canRx.rx_frame[i].data[j]);
            }
            printf("\n");
        }
    }
}
