/*
 * mpu6050.h
 *
 *  Created on: Apr 2, 2022
 *      Author: Akeman
 */

#ifndef SENSORS_MPU6050_MPU6050_H_
#define SENSORS_MPU6050_MPU6050_H_

#include <stdbool.h>

#include <ti/sysbios/knl/Semaphore.h>

enum
{
    MPU6050_SELF_TEST_X = 0x0d,
    MPU6050_SELF_TEST_Y = 0x0e,
    MPU6050_SELF_TEST_Z = 0x0f,
    MPU6050_SELF_TEST_A = 0x10,
    MPU6050_SAMPLE_RATE_DIVIDER = 0x19,
    MPU6050_CONFIG = 0x1a,
    MPU6050_GYRO_CONFIG = 0x1b,
    MPU6050_ACCEL_CONFIG = 0x1c,
    MPU6050_FIFO_EN = 0x23,

    MPU6050_I2C_MST_CTRL = 0x24,
    MPU6050_2C_SLV0_ADDR = 0x25,
    MPU6050_I2C_SLV0_REG = 0x26,
    MPU6050_I2C_SLV0_CTRL = 0x27,
    MPU6050_I2C_SLV1_ADDR = 0x28,
    MPU6050_I2C_SLV1_REG = 0x29,
    MPU6050_I2C_SLV1_CTRL = 0x2a,
    MPU6050_I2C_SLV2_ADDR = 0x2b,
    MPU6050_I2C_SLV2_REG = 0x2c,
    MPU6050_I2C_SLV2_CTRL = 0x2d,
    MPU6050_I2C_SLV3_ADDR = 0x2e,
    MPU6050_I2C_SLV3_REG = 0x2f,
    MPU6050_I2C_SLV3_CTRL = 0x30,
    MPU6050_I2C_SLV4_ADDR = 0x31,
    MPU6050_I2C_SLV4_REG = 0x32,
    MPU6050_I2C_SLV4_DO = 0x33,
    MPU6050_I2C_SLV4_CTRL = 0x34,
    MPU6050_I2C_SLV4_DI = 0x35,
    MPU6050_I2C_MST_STATUS = 0x36,
    MPU6050_INT_PIN_CFG = 0x37,
    MPU6050_INT_ENABLE = 0x38,
    MPU6050_INT_STATUS = 0x3a,

    MPU6050_ACCEL_XOUT_H = 0x3b,
    MPU6050_ACCEL_XOUT_L = 0x3c,

    MPU6050_ACCEL_YOUT_H = 0x3d,
    MPU6050_ACCEL_YOUT_L = 0x3e,

    MPU6050_ACCEL_ZOUT_L = 0x3f,
    MPU6050_ACCEL_ZOUT_H = 0x40,

    MPU6050_TEMP_OUT_H = 0x41,
    MPU6050_TEMP_OUT_L = 0x42,

    MPU6050_GYRO_XOUT_H = 0x43,
    MPU6050_GYRO_XOUT_L = 0x44,

    MPU6050_GYRO_YOUT_H = 0x45,
    MPU6050_GYRO_YOUT_L = 0x46,

    MPU6050_GYRO_ZOUT_H = 0x47,
    MPU6050_GYRO_ZOUT_L = 0x48,


    MPU6050_I2C_SLV0_DO = 0x63,
    MPU6050_I2C_SLV1_DO = 0x64,
    MPU6050_I2C_SLV2_DO = 0x65,
    MPU6050_I2C_SLV3_DO = 0x66,
    MPU6050_I2C_MST_DELAY_CTRL = 0x67,

    MPU6050_SIGNAL_PATH_RESET = 0x68,
    MPU6050_USER_CTRL = 0x6a,
    MPU6050_PWR_MGMT_1 = 0x6b,
    MPU6050_PWR_MGMT_2 = 0x6c,
    MPU6050_FIFO_COUNTH = 0x72,
    MPU6050_FIFO_COUNTL = 0x73,
    MPU6050_FIFO_R_W = 0x74,
    MPU6050_WHO_AM_I = 0x75
} MPU6050_Registers;

enum
{
    MPU6050_GYRO_CONFIG_250_DEG_PER_S = 0,
    MPU6050_GYRO_CONFIG_500_DEG_PER_S = 0x08,
    MPU6050_GYRO_CONFIG_1000_DEG_PER_S = 0x10,
    MPU6050_GYRO_CONFIG_2000_DEG_PER_S = 0x18,
    MPU6050_GYRO_CONFIG_SELF_TEST_Z = 0x20,
    MPU6050_GYRO_CONFIG_SELF_TEST_Y = 0x40,
    MPU6050_GYRO_CONFIG_SELF_TEST_X = 0x80
} MPU6050_GyroscopeConfiguration;

enum
{
    MPU6050_ACC_CONFIG_2G = 0,
    MPU6050_ACC_CONFIG_4G = 0x08,
    MPU6050_ACC_CONFIG_8G = 0x10,
    MPU6050_ACC_CONFIG_16G = 0x18,
    MPU6050_ACC_CONFIG_SELF_TEST_Z = 0x20,
    MPU6050_ACC_CONFIG_SELF_TEST_Y = 0x40,
    MPU6050_ACC_CONFIG_SELF_TEST_X = 0x80
} MPU6050_AccelerometerConfiguration;

enum
{
    MPU6050_RESET_TEMP = 0x01,
    MPU6050_RESET_ACC = 0x02,
    MPU6050_RESET_GYRO = 0x04
} MPU6050_SignalPathReset;

enum
{
    MPU6050_RESET = 0x01,
    MPU6050_I2C_MASTER_RESET = 0x02,
    MPU6050_FIFO_RESET = 0x04,
    MPU6050_I2C_DISABLE = 0x10,
    MPU6050_I2C_MASTER_MODE = 0x20,
    MPU6050_FIFO_ENABLE = 0x40
} MPU6050_UserControl;

enum
{
    MPU6050_DATA_READY_INT_EN = 0x01,
    MPU6050_I2C_MASTER_INT_EN = 0x08,
    MPU6050_FIFO_OVERFLOW_INT_EN = 0x10
} MPU6050_InterruptEnable;

enum
{
    MPU6050_DATA_READY_INT = 0x1,
    MPU6050_I2C_MASTER_INT = 0x08,
    MPU6050_FIFO_OVERFLOW_INT = 0x10
} MPU6050_InterruptStatus;

enum
{
    MPU6050_PLL_X_GYRO_REF = 0x01,
    MPU6050_PLL_EXTERNAL_32dot768kHz = 0x04,
    MPU6050_TEMPERATURE_DISABLE = 0x08,
    MPU6050_SLEEP_DISABLE = 0x20,
    MPU6050_SLEEP_ENABLE = 0x40,
    MPU6050_DEVICE_RESET = 0x80
} MPU6050_PowerManagement1;

enum
{
    MPU6050_INPUT_DISABLED = 0
} MPU6050_Config;

enum
{
    MPU6050_FIFO_ACC = 0x8,
    MPU6050_FIFO_GYRO = 0x70,
    MPU6050_FIFO_TEMP = 0x80
} MPU6050_FIFO;

typedef struct __attribute__ ((__packed__))
{
    double accelX;
    double accelY;
    double accelZ;
    double temperature;
    double gyroX;
    double gyroY;
    double gyroZ;
    bool valid;
} MPU6050_Data;

typedef struct __attribute__ ((__packed__))
{
    uint32_t overflowCounter;
    uint32_t fifoCountPeak;
    uint32_t dataInvalidCounter;
} MPU6050_Comstats;

void openI2C(void);
void initMPU6050(void);
void readAccelerometer(void);
void readGyroscope(void);
void readTemperature(void);
uint16_t getFifoCount(void);
bool getFifoValues(MPU6050_Data* const convertedData);
uint8_t getInterruptStatus(void);

extern Semaphore_Struct mpu6050InterruptSemaphoreStruct;
extern Semaphore_Handle mpu6050InterruptSemaphoreHandle;

#endif /* SENSORS_MPU6050_MPU6050_H_ */
