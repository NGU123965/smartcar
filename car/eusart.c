#include "eusart.h"
#include "stdint.h"

void init_EUSART() {
    // configure EUSART BAUD RATE 9600
    // USB TO TTL 的 TXD 连接至 RB4， RXD连接至RB5
    ANSELBbits.ANSB4 = 1;
    ANSELBbits.ANSB5 = 1;
    TRISB4 = 1;
    TRISB5 = 1;
    RB5PPS = 0x10;
    RXPPS = 0x0c;
    PIE3bits.TXIE = 0;
    TX1STAbits.TXEN = 1;
    TX1STAbits.SYNC = 0;
    RC1STAbits.SPEN = 1;
    BAUD1CONbits.BRG16 = 0;
    TX1STAbits.BRGH = 1;
    SPBRG = 207;
}

void transmitData(unsigned char data) {
    while(!TRMT);
    TXREG = data;
}

void transmitStr(char* buf) {
    int i = 0;
    while(buf[i] != '\0')
        transmitData(buf[i++]);
}

void transmitFrame(uint8_t* frame, uint8_t dataSize) {
    transmitData(0x01);
    for (uint8_t i = 0; i < dataSize; i++) {
        transmitData(frame[i]);
    }
    transmitData(0xfe);
}