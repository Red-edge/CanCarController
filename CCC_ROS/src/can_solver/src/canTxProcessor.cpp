/*

Program:        CanCarController
Name:           CanTxProcessor
Version:        1.1.0
Date:           24.9.14
Developer:      Rededge
Desc:           Process the CAN TX and store them in cache; class declared; successed in connecting systick and canTxProcessor, failed to connect with canRx

*/

#include "canTxProcessor.hpp"

void canTxProcessor::init_canTx(const char *canname, uint64_t curtick)
{

    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    cout << "Tx sockfd " << sockfd << endl;
    // 用于创建网络套接字以及套接字代号，分别指定了：协议族（Protocol Family），套接字类型，协议编号
    // 该语句会创建一个 CAN 网络的原始套接字，并返回一个套接字文件描述符（sockfd）。可以使用这个文件描述符来发送和接收 CAN 帧。
    // 当使用CAN总线（PF_CAN）或其他硬件协议时，如果硬件设备未正确初始化或未连接，可能会导致套接字创建失败。
    if (0 > sockfd)
    {
        perror("socket error");
        exit(EXIT_FAILURE);
        // return 0;
    }

    strcpy(ifr.ifr_name, canname); // 指定Can通道名，注意提交名字
    // Interface request structure
    cout << "Ifr name " << ifr.ifr_name << endl;
    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == -1)
    // 通过ioctl系统调用，使用SIOCGIFINDEX获取can的索引号和ifr_name
    // GPT解释为：通过ioctl系统调用，使用SIOCGIFINDEX获取can的索引号和ifr_name
    // SIOCGIFINDEX 的全称是 "Socket IOCTL Get Interface Index"
    // SIOCGIFINDEX的含义是获取接口索引，也就是从sockfd指向的套接字查询到接口索引，并填入ifr指向的ifindex
    {
        std::cerr << "Failed to get CAN interface index" << std::endl;
        printf("%s\n", strerror(errno));
        close(sockfd);
        // return 1;
        // init_canTx(canname);
    }
    // cout << "&Ifr name " << ifr.ifr_name << endl;

    can_addr.can_family = AF_CAN; // 填充数据
    can_addr.can_ifindex = ifr.ifr_ifindex;

    /* 将套接字与 can0 进行绑定 */
    ret = bind(sockfd, (struct sockaddr *)&can_addr, sizeof(can_addr));
    // 将套接字和can网络接口绑定
    // 通过这行代码，你将套接字 sockfd 绑定到了 CAN 网络接口，can_addr 中指定了接口索引和地址族。
    // 这个绑定操作使得接下来的数据发送或接收操作都通过指定的 CAN 接口（如 can0 或 vcan0）进行。
    cout << "canTx ret: " << ret << endl;
    if (0 > ret)
    {
        perror("bind error");
        close(sockfd);
        exit(EXIT_FAILURE);
        // return 0;
    }

    // 准备Can信号，这里先只考虑2006电机了
    std::memset(&tx_frame, 0, sizeof(tx_frame));
    tx_frame.can_id = 0x200; // 设置 CAN ID
    tx_frame.can_dlc = 8;    // 设置数据长度为 8 字节
    std::memcpy(tx_frame.data, tx_tmp, 8);

    can_addr.can_family = AF_CAN; // 填充数据
    can_addr.can_ifindex = ifr.ifr_ifindex;

    Lasttick = curtick;

    cout << "Init canTx success!" << endl;
    // return 0;
}

void canTxProcessor::canNTx(uint64_t curtick)
{
    std::memcpy(tx_frame.data, tx_tmp, 8);
    txcheck = write(sockfd, &tx_frame, sizeof(tx_frame)); // 用于将信息tx_frame写入sockfd指代的套接字
    // cout << sockfd << endl;
    Lasttick = curtick;
    if (txcheck == -1)
    {
        std::cerr << "Failed to send CAN message" << std::endl;
        printf("%s\n", strerror(errno));
        // close(sockfd);
        return;
    }
    if (txcheck < sizeof(tx_frame))
    {
        cout << "Only write partial data." << endl;
    }
}

