#include <xc.h>
#include <stdint.h>
#include "pic16f18854.h"
#include "init.h"
#include "eusart.h"
#include "syn480r.h"
#include "pwm.h"

void init_hardware(void) {
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;

    LATA = 0;
    LATB = 0;
    LATC = 0;

    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;

    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    
    GIE = 1;
    PEIE = 1;
    init_tmr0();
    init_EUSART();
    init_syn480r();
    pwm_init();
}

void init_tmr0(void) {
    TMR0IE = 1;                 // 允许TMR0中断
    T0CON0bits.T0EN = 1;        // TMR0 使能位
    T0CON0bits.T016BIT = 0;     // 8位模式
    T0CON0bits.T0OUTPS0 = 0;    
    T0CON0bits.T0OUTPS1 = 0;
    T0CON0bits.T0OUTPS2 = 0;
    T0CON0bits.T0OUTPS3 = 0;    // T0OUTPS = 0000, 1:1后分频比
    T0CON1bits.T0CKPS0 = 0;
    T0CON1bits.T0CKPS1 = 1;
    T0CON1bits.T0CKPS2 = 0;
    T0CON1bits.T0CKPS3 = 0;     // T1CKPS = 0010, 1:4预分频比
    T0CON1bits.T0CS0 = 0;
    T0CON1bits.T0CS1 = 1;
    T0CON1bits.T0CS2 = 0;       // 时钟源选择 Fosc/4 = 8 Mhz
    T0CON1bits.T0ASYNC = 0;
    reset_tmr0();
}

void reset_tmr0(void) {
    // TMR0计时时间为 1 * 1 * 200 / 8Mhz = 25us
    TMR0H = 0xC7;               // TMR0H = 200 - 1 = 199
    TMR0IF = 0;
}