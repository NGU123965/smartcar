#include "led.h"

void LED_ON(uint8_t led_num) {
    switch (led_num) {
        case 1:
            PORTAbits.RA6 = 1;
            break;
        case 2:
            PORTCbits.RC0 = 1;
            break;
        case 3:
            PORTCbits.RC1 = 1;
            break;
        case 4:
            PORTCbits.RC2 = 1;
            break;
    }
}

void LED_ALL_ON(void) {
    LED_ON(1);
    LED_ON(2);
    LED_ON(3);
    LED_ON(4);
}

void LED_ALL_OFF(void) {
    PORTAbits.RA6 = 0;
    PORTC = 0;
}

void LED_3_OFF(void) {
    PORTC = 0;
}