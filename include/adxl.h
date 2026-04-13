#ifndef ADXL_H
#define ADXL_H
#include <fcntl.h>      // For open()
#include <unistd.h>     // For read(), write(), close()
#include <sys/ioctl.h>  // For ioctl()
#include <linux/i2c-dev.h> // For I2C_SLAVE constant
#include <i2c/smbus.h>
#include <stdio.h>      // For printf/debugging
#include <stdint.h>
#include "i2c_master.h"

#define resolution 0.0039
#define ADXL_BASE_ADDRESS 0x53
#define POWER_CONTROL 0x2D
#define DATA_FORMAT 0x31
#define DEVID 0x00
#define DATAX0 0x32
#define THRESH_ACT 0x24
#define INT_ENABLE 0x2E
#define INT_MAP 0x2F
#define INT_SOURCE 0x30

typedef enum {
    RANGE_2G,
    RANGE_4G,
    RANGE_8G,
    RANGE_16G,
    ALL_RANGE, //only to switch between ranges
} RANGE_t;


//Function Declarations
int adxl_init();
int adxl_range(volatile RANGE_t range);
int adxl_read(float *x,float *y,float *z);
int adxl_interrupts(int fd);
int interrupt_clear(void);
#endif