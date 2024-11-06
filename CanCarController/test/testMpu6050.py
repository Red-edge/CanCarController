import smbus
import math
import time

# 设置寄存器地址
PWR_MGMT_1 = 0x6B
ACCEL_XOUT_H = 0x3B
ACCEL_YOUT_H = 0x3D
ACCEL_ZOUT_H = 0x3F

# 初始化I2C设备
bus = smbus.SMBus(1)
mpu_address = 0x68

# 唤醒MPU6050
bus.write_byte_data(mpu_address, PWR_MGMT_1, 0)

def read_raw_data(addr):
    # 读取原始数据（高位和低位字节）
    high = bus.read_byte_data(mpu_address, addr)
    low = bus.read_byte_data(mpu_address, addr+1)
    value = ((high << 8) | low)
    # 转换为有符号数
    if value > 32768:
        value -= 65536
    return value

def get_angles():
    # 获取加速度计数据
    acc_x = read_raw_data(ACCEL_XOUT_H)
    acc_y = read_raw_data(ACCEL_YOUT_H)
    acc_z = read_raw_data(ACCEL_ZOUT_H)

    # 计算角度
    roll = math.atan2(acc_y, acc_z) * 180 / math.pi
    pitch = math.atan2(-acc_x, math.sqrt(acc_y**2 + acc_z**2)) * 180 / math.pi
    
    return roll, pitch

while True:
    roll, pitch = get_angles()
    print("当前翻滚角（Roll）： {:.2f}°".format(roll))
    print("当前俯仰角（Pitch）：{:.2f}°\n".format(pitch))
    time.sleep(0.1)
