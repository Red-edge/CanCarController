#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define MPU6050_ADDR 0x68 // MPU6050 I2C 地址
#define PWR_MGMT_1 0x6B   // 电源管理寄存器

int main()
{
    // 打开 I2C 设备
    int file = open("/dev/i2c-1", O_RDWR);
    if (file < 0)
    {
        std::cerr << "Failed to open the I2C bus" << std::endl;
        return 1;
    }

    // 设置 I2C 地址
    if (ioctl(file, I2C_SLAVE, MPU6050_ADDR) < 0)
    {
        std::cerr << "Failed to connect to the device" << std::endl;
        return 1;
    }

    // 初始化 MPU6050（解除复位）
    uint8_t buf[2] = {PWR_MGMT_1, 0}; // 向 PWR_MGMT_1 寄存器写 0
    if (write(file, buf, 2) != 2)
    {
        std::cerr << "Failed to initialize MPU6050" << std::endl;
        return 1;
    }
    while (1)
    {
        // 读取加速度计数据（假设加速度计数据存储在 0x3B 和 0x3C）
        uint8_t reg = 0x3B; // 加速度计数据的起始寄存器
        if (write(file, &reg, 1) != 1)
        {
            std::cerr << "Failed to write register address" << std::endl;
            return 1;
        }

        // 读取 6 字节数据（X, Y, Z 加速度）
        uint8_t data[6] = {0};
        if (read(file, data, 6) != 6)
        {
            std::cerr << "Failed to read data" << std::endl;
            return 1;
        }

        // 处理数据，转换为加速度值
        int16_t ax = (data[0] << 8) | data[2];
        int16_t ay = (data[2] << 8) | data[4];
        int16_t az = (data[4] << 8) | data[6];

        std::cout << "Acceleration X: " << ax << std::endl;
        std::cout << "Acceleration Y: " << ay << std::endl;
        std::cout << "Acceleration Z: " << az << std::endl;

        sleep(1);
    }

    close(file); // 关闭 I2C 设备
    return 0;
}
