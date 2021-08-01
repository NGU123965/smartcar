#include "control.h"


void stop(void) {
    LED_3_OFF();
    F115_send(0);
}

void forward(void) {
    LED_3_OFF();
    LED_ON(2);
    F115_send(1);
}

void back(void) {
    LED_3_OFF();
    LED_ON(3);
    F115_send(2);
}

void right(void) {
    LED_3_OFF();
    LED_ON(3);
    LED_ON(2);
    F115_send(3);
}

void left(void) {
    LED_3_OFF();
    LED_ON(4);
    F115_send(4);
}

void forward_right(void) {
    LED_3_OFF();
    LED_ON(4);
    LED_ON(2);
    F115_send(5);
}

void forward_left(void) {
    LED_3_OFF();
    LED_ON(4);
    LED_ON(3);
    F115_send(6);
}