#include <xc.h>
#include <pic16f18854.h>
#include <stdint.h>
#include "pwm.h"

void pwm_init(void) {
    // 通过将相关的 TRIS 位置 1，禁止 PWMx 引脚输出驱动器
    TRISC0 = 1;
    TRISC1 = 1;
    TRISC2 = 1;
    TRISC3 = 1;
    // 清零 PWMxCON 寄存器
    CCP1CON = 0;
    // 将 PWM 周期值装入 T2PR 寄存器
    T2PR = 255;
    // 将 PWM 占空比值装入 PWMxDCH 寄存器和 PWMxDCL 寄存器的 bit <7:6>
    CCPR1H = 0b11111111;    // 高8位
    CCPR1L = 0b11000000;    // 低2位，占空比为0/1024 = 0
    CCPR2H = 0b11111111;    // 高8位
    CCPR2L = 0b11000000;    // 低2位，占空比为0/1024 = 0
    CCPR3H = 0b11111111;    // 高8位
    CCPR3L = 0b11000000;    // 低2位，占空比为0/1024 = 0
    CCPR4H = 0b11111111;    // 高8位
    CCPR5L = 0b11000000;    // 低2位，占空比为0/1024 = 0
    // 配置并启动 Timer2
    TMR2IE = 0;
    TMR2IF = 0;
    T2CLKCON = 0b00000001;  // 配置tmr2的时钟输入为Fosc/4 = 8Mhz
    T2CONbits.CKPS0 = 0;
    T2CONbits.CKPS1 = 0;
    T2CONbits.CKPS2 = 0;    // 配置tmr2的预分频为1:1
    T2CONbits.ON = 1;       // 使能TMR2
    
    // PWM 周期为 = （255 + 1）* 4 / 32Mhz * 1 = 32 us, 即 PWM频率为 31.25Khz
    // PWM 分辨率为 10 位
    while (!TMR2IF);
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISC3 = 0;
    RC0PPS = 0x0c;          // CCP4 -> RC0
    RC1PPS = 0x0b;          // CCP3 -> RC1
    RC2PPS = 0x09;          // CCP1 -> RC2
    RC3PPS = 0x0a;          // CCP2 -> RC3
    // 通过将相应值装入 PWMxCON 寄存器来配置 PWM 模块
    CCP1CON = 0b10011111;
    CCP2CON = 0b10011111;
    CCP3CON = 0b10011111;
    CCP4CON = 0b10011111;
    TRISA7 = 0;
    RA7 = 1; // 使能驱动芯片
}

void set_pwm(uint8_t num, uint8_t power) {
    switch (num) {
        case 1:
            CCPR1H = power;
            break;
        case 2:
            CCPR2H = power;
            break;
        case 3:
            CCPR3H = power;
            break;
        case 4:
            CCPR4H = power;
            break;
    }
}
