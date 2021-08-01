#define _XTAL_FREQ 32000000UL

#include "f115.h"
#include "stdint.h"

#define time_offset 400

void F115_init() {
    TRISCbits.TRISC3 = 0; // configure RC3 as output
}

void F115_send(uint8_t data) {
    uint8_t i;
    // 0 -> stop; 1 -> forward; 2 -> back; 3 -> right; 4 -> left; 5 -> forward_right; 6 -> forward_left;
    // send 3 times
    for (i = 0; i < 3; i++) {
        switch(data) {
        case 0:
            F115_header();
            F115_send_b0();
            F115_send_b0();
            F115_send_b0();
            F115_end();
            break;
        case 1:
            F115_header();
            F115_send_b0();
            F115_send_b0();
            F115_send_b1();
            F115_end();
            break;
        case 2:
            F115_header();
            F115_send_b0();
            F115_send_b1();
            F115_send_b0();
            F115_end();
            break;
        case 3:
            F115_header();
            F115_send_b0();
            F115_send_b1();
            F115_send_b1();
            F115_end();
            break;
        case 4:
            F115_header();
            F115_send_b1();
            F115_send_b0();
            F115_send_b0();
            F115_end();
            break;
        case 5:
            F115_header();
            F115_send_b1();
            F115_send_b0();
            F115_send_b1();
            F115_end();
        case 6:
            F115_header();
            F115_send_b1();
            F115_send_b1();
            F115_send_b0();
            F115_end();
    }
    }
}

void F115_send_b1() {
    Pin_DAT = 1;
    __delay_us(2000);
    Pin_DAT = 0;
    __delay_us(2000);
}

void F115_send_b0() {
    Pin_DAT = 1;
    __delay_us(2000);
    Pin_DAT = 0;
    __delay_us(4000);
}

void F115_header() {
    Pin_DAT = 1;
    __delay_us(2000);
    Pin_DAT = 0;
    __delay_us(6000);
}

void F115_end() {
    Pin_DAT = 1;
    __delay_us(2000);
    Pin_DAT = 0;
    __delay_us(8000);
    Pin_DAT = 1;
}