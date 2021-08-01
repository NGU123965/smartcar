#include <xc.h>
#include <stdio.h>
#include <pic16f18854.h>
#include "syn480r.h"
#include "eusart.h"
#include "motor.h"

uint8_t LL_w, HH_w, RFBIT;
uint8_t data_recv[10];
uint8_t bit_cnt = 0;
uint8_t start = 0;
uint16_t null_cnt = 0;
char buffer[40];

void success(void);
void fail(void);

void init_syn480r(void) {
    TRISA0 = 1;
    ANSA0 = 0;
    LL_w = HH_w = 0;
}

uint8_t get_raw_signal(void) {
    return RA0;
}

void handle_wireless_control(void) {
    if (!RA0) {
        // 低电平
        LL_w ++;
        RFBIT = 0;
        if (LL_w > 3) {
            HH_w = 0;
        }
    } else {
        // 高电平
        HH_w ++;
        if (!RFBIT) {
            if (HH_w > 3) {
                RFBIT = 1;
            }
            if (RFBIT) {
                // 由低电平跳变到高电平，根据上一个低电平的宽度判断比特信息
                if (start == 0) {
                    // start = 0, 没有同步过初值0
                    if (LL_w > 60 && LL_w < 70) {
                        start = 1;
                        bit_cnt = 0;
                    }
                } else {
                    // start = 0, 已经同步了初值0, 开始解析数据比特
                    if (LL_w > 15 && LL_w < 35) {
                        // bit 1
                        data_recv[bit_cnt++] = 1;
                    } else if (LL_w < 50) {
                        // bit 0
                        data_recv[bit_cnt++] = 0;
                    } else if (LL_w > 75 && LL_w < 90 && bit_cnt == 3) {
                        // end
                        if (data_recv[0] == 0) {
                            if (data_recv[1] == 0) {
                                if (data_recv[2] == 0) {
                                    // 000 -> stop
                                    stop();
                                    success();
                                } else {
                                    // 001 -> forward
                                    forward();
                                    success();
                                }
                            } else {
                                if (data_recv[2] == 0) {
                                    // 010 -> back
                                    back();
                                    success();
                                } else {
                                    // 011 -> right
                                    forward_right();
                                    success();
                                }
                            }
                        } else if (data_recv[1] == 0 && data_recv[2] == 0) {
                            // 100 -> left
                            forward_left();
                            success();
                        }
                    } else {
                        // error
                        LL_w = 0;
                        start = 0;
                        bit_cnt = 0;
                    }
                }
                LL_w = 0;
            }
        }
    }
    fail();
}

void success(void) {
    null_cnt = 0;
}

void fail(void) {
    null_cnt ++;
    if (null_cnt > 10000) {
        stop();
        null_cnt = 0;
    }
}