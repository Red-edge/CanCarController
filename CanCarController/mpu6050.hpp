#include <wiringPiI2C.h>
#include <iostream>
#include <unistd.h>

#define MPU6050_ADDR 0x68  // MPU6050 I2C 地址

// MPU6050 寄存器地址
#define PWR_MGMT_1    0x6B
#define ACCEL_XOUT_H  0x3B
#define ACCEL_YOUT_H  0x3D
#define ACCEL_ZOUT_H  0x3F
#define GYRO_XOUT_H   0x43
#define GYRO_YOUT_H   0x45
#define GYRO_ZOUT_H   0x47

class MPU6050 {
public:
    // 存储加速度和陀螺仪数据的结构体
    struct Data {
        int accel_x, accel_y, accel_z;
        int gyro_x, gyro_y, gyro_z;
    };
    Data data;
    MPU6050() : fd(-1) {}

    // 初始化 MPU6050 设备
    bool initialize() {
        fd = wiringPiI2CSetup(MPU6050_ADDR);
        if (fd == -1) {
            std::cerr << "无法初始化 I2C 设备" << std::endl;
            return false;
        }
        wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0);  // 解除睡眠模式
        return true;
    }

    // 读取 MPU6050 数据
    Data readData() {
        data.accel_x = readWord2C(ACCEL_XOUT_H);
        data.accel_y = readWord2C(ACCEL_YOUT_H);
        data.accel_z = readWord2C(ACCEL_ZOUT_H);
        data.gyro_x = readWord2C(GYRO_XOUT_H);
        data.gyro_y = readWord2C(GYRO_YOUT_H);
        data.gyro_z = readWord2C(GYRO_ZOUT_H);
        return data;
    }

private:
    int fd;  // 文件描述符，用于 I2C 设备通信

    // 读取 16 位寄存器数据并处理负数值
    int readWord2C(int addr) {
        int high = wiringPiI2CReadReg8(fd, addr);
        int low = wiringPiI2CReadReg8(fd, addr + 1);
        int value = (high << 8) + low;
        if (value >= 0x8000)
            value = -(65536 - value);
        return value;
    }
};
