#include "DS3231.h"

//int fd;
uint8_t decTobcd(uint8_t val) {
    return ((val/10)<<4 | (val%10));
}

uint8_t bcdTodec(uint8_t val) {
    return ((val>>4)*10) + (val&0x0F);
}

int DS3231_init() {
    uint8_t status;
    if(I2Cread(fd,DS3231_BASE_ADDRESS,STATUS,&status) < 0) {
        perror("Error");
        return -1;
    }
    if (status & 0x80) { // Check if Bit 7 is 1
    printf("Warning: RTC Oscillator was stopped (power loss)\n");
    //clearing the flag
    status &= ~(0x80);
    I2Cwrite(fd, DS3231_BASE_ADDRESS, STATUS, status);
    }
    return 0;
}

int DS3231_set_time(RTC_Time_t *rtc) {
    uint8_t buffer[7];

    buffer[0] = decTobcd(rtc->seconds);
    buffer[1] = decTobcd(rtc->minutes);
    buffer[2] = decTobcd(rtc->hours);     // Assumes 24h mode
    buffer[3] = decTobcd(rtc->day);
    buffer[4] = decTobcd(rtc->date);
    buffer[5] = decTobcd(rtc->month);
    buffer[6] = decTobcd(rtc->year - 2000); // Store as 26 for 2026
    // Write all 7 bytes starting at the SECONDS register (0x00)
    return I2Cwrite_mul(fd, DS3231_BASE_ADDRESS, SECONDS, buffer, 7);
}


int DS3231_get_time(RTC_Time_t *rtc) {
    uint8_t buffer[8];
    if(I2Cread_mul(fd,DS3231_BASE_ADDRESS,SECONDS,buffer,7) < 0) {
        perror("Error");
        return -1;
    }
    rtc->seconds = bcdTodec(buffer[0]);
    rtc->minutes = bcdTodec(buffer[1]);
    rtc->hours = bcdTodec(buffer[2] & 0x3F); //masking for 24 mode
    rtc->day = bcdTodec(buffer[3]);
    rtc->date = bcdTodec(buffer[4]);
    rtc->month = bcdTodec(buffer[5] & 0x1F); //masking centuary bit
    rtc->year = bcdTodec(buffer[6]) + 2000; //to get in 2000 format
    return 0;

}