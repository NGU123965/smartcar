#include "i2c.h"
#include <stdlib.h>


#define MAX_READ_BUFFER_SIZE 20
uint8_t recievedData[MAX_READ_BUFFER_SIZE];

void initIICCenterMode() {
    // Using MSSP2 module
    // Set RB1(SCL) RB2(SDA) as input mode for iic center mode
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    WPUBbits.WPUB1 = 1;
    WPUBbits.WPUB2 = 1;
    SSP1CLKPPS = 0x09;
    SSP1DATPPS = 0x0A;
    RB1PPS = 0x14;
    RB2PPS = 0x15;

    //Initialize IIC
    SSP1CON1bits.SSPEN = 1;
    //Set as IIC center mode
    SSP1CON1bits.SSPM0 = 0;
    SSP1CON1bits.SSPM1 = 0;
    SSP1CON1bits.SSPM2 = 0;
    SSP1CON1bits.SSPM3 = 1;
    //Set IIC baud speed as 100kHz (System clock is 32MHz)
    SSP1ADD = 79;
}

uint8_t* centerReadFromPeripheral(uint8_t peripheralAddr, uint8_t dataSize) {
    if (dataSize <= 0) {
        return NULL;
    }
    IIC_Start();         //Start condition
    IIC_Write_Byte((uint8_t)(peripheralAddr << 1) + 1);     //7 bit address + Read
    for (uint8_t i = 0; i < dataSize; i++) {
        if (i == dataSize - 1) {
            recievedData[i] = IIC_Read_Byte(1);
        } else {
            recievedData[i] = IIC_Read_Byte(0);
        }
    }
    IIC_Stop();          //Stop condition
    return recievedData;
}

void centerWriteToPeripheral(uint8_t peripheralAddr, uint8_t* data, uint8_t dataSize) {
    IIC_Start();         //Start condition
    IIC_Write_Byte((uint8_t)(peripheralAddr << 1) + 0);     //7 bit address + Write
    for (uint8_t i = 0; i < dataSize; i++) {
        IIC_Write_Byte(data[i]);
    }
    IIC_Stop();          //Stop condition
}

uint8_t IIC_Read_Byte(uint8_t ack) {
    //Read one byte
    uint8_t b;
    
    SSP1CON2bits.RCEN = 1; //使能IIC接收模式
    while (!SSP1IF);
    SSP1IF = 0;
    b = SSP1BUF;
    SSP1STATbits.BF = 0;
    IIC_ACK(ack);
    return b;
}

void IIC_Write_Byte(uint8_t d) {
    SSP1BUF = d; //将从机地址装入SSPBUF进行传送,以准备进行数据读
    while (!SSP1IF); //等待发送结束
    SSP1IF = 0; //SSPIF标志清0
}

void IIC_ACK(uint8_t ack) {
    //The master ACK 0 or 1
    SSP1CON2bits.ACKDT = (ack & 0x01); //ACK 0 or 1, 0 is active
    SSP1CON2bits.ACKEN = 1; //在SDA和SCL引脚上启动应答顺序，并发送ACKDT数据位
    while (!SSP1IF); //等待应答发送结束
    SSP1IF = 0; //SSPIF标志清0
}

void IIC_Start() {
    SSP1CON2bits.SEN = 1; // Start signal
    while(!SSP1IF);
    SSP1IF = 0; //SSPIF标志清0
}

void IIC_Stop() {
    SSP1CON2bits.PEN = 1; //产生IIC停止信号
    while (!SSP1IF); //等待发送结束
    SSP1IF = 0; //SSPIF标志清0
}