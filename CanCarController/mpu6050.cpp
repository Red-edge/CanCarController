// #include <iostream>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/ioctl.h>
// #include <linux/i2c-dev.h>
// #include <string>
// #include <cstdint>

// using namespace std;

// class MPU6050
// {
// public:
//     // 构造函数：传入 I2C 设备文件路径
//     MPU6050(const std::string &device) : file(-1), device(device) {}

//     // 析构函数：关闭 I2C 设备
//     ~MPU6050()
//     {
//         if (file >= 0)
//         {
//             close(file);
//         }
//     }

//     // 初始化 MPU6050
//     bool initialize()
//     {
//         // 打开 I2C 设备
//         file = open(device.c_str(), O_RDWR);
//         if (file < 0)
//         {
//             std::cerr << "Failed to open the I2C bus" << std::endl;
//             return false;
//         }

//         // 设置 I2C 地址
//         if (ioctl(file, I2C_SLAVE, MPU6050_ADDR) < 0)
//         {
//             std::cerr << "Failed to connect to the device" << std::endl;
//             return false;
//         }

//         // 初始化 MPU6050（解除复位）
//         uint8_t buf[2] = {PWR_MGMT_1, 0}; // 向 PWR_MGMT_1 寄存器写 0，解除复位
//         if (write(file, buf, 2) != 2)
//         {
//             std::cerr << "Failed to initialize MPU6050" << std::endl;
//             return false;
//         }

//         return true;
//     }

//     // 读取加速度计数据
//     bool readAccelerometer(int16_t &ax, int16_t &ay, int16_t &az)
//     {
//         uint8_t reg = ACCEL_XOUT_H;

//         // 写入寄存器地址
//         if (write(file, &reg, 1) != 1)
//         {
//             std::cerr << "Failed to write register address" << std::endl;
//             return false;
//         }

//         // 读取 6 字节加速度计数据（X, Y, Z）
//         uint8_t data[6] = {0};
//         if (read(file, data, 6) != 6)
//         {
//             std::cerr << "Failed to read data" << std::endl;
//             return false;
//         }

//         // 将高低字节组合成 16 位数据
//         ax = (data[0] << 8) | data[1];
//         ay = (data[2] << 8) | data[3];
//         az = (data[4] << 8) | data[5];

//         return true;
//     }

// private:
//     int file;                                 // I2C 文件描述符
//     std::string device;                       // 设备路径
//     static const uint8_t MPU6050_ADDR = 0x68; // MPU6050 I2C 地址
//     static const uint8_t PWR_MGMT_1 = 0x6B;   // 电源管理寄存器
//     static const uint8_t ACCEL_XOUT_H = 0x3B; // 加速度计数据寄存器起始地址
// };

// int main()
// {
//     // 创建 MPU6050 对象并初始化
//     MPU6050 mpu("/dev/i2c-1");
//     if (!mpu.initialize())
//     {
//         std::cerr << "MPU6050 initialization failed" << std::endl;
//         return -1;
//     }

//     while (1)
//     {
//         // 读取加速度计数据
//         int16_t ax, ay, az;
//         if (mpu.readAccelerometer(ax, ay, az))
//         {
//             std::cout << "Accelerometer data: " << std::endl;
//             std::cout << "X: " << ax << ", Y: " << ay << ", Z: " << az << std::endl;
//             cout << endl;
//         }
//         else
//         {
//             std::cerr << "Failed to read accelerometer data" << std::endl;
//             return -1;
//         }
//         // sleep(1);
//     }

//     return 0;
// }