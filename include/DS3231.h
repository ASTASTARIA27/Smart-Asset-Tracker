#ifndef DS3231_H
#define DS3231_H
#include "i2c_master.h"

#define DS3231_BASE_ADDRESS 0x68
#define STATUS 0x0F
#define SECONDS 0x00

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint16_t year;
} RTC_Time_t;

//Function Declarations
uint8_t decTobcd(uint8_t val);
uint8_t bcdTodec(uint8_t val);
int DS3231_init();
int DS3231_get_time(RTC_Time_t *rtc);
int DS3231_set_time(RTC_Time_t *rtc);

#endif