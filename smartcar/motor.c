#include <xc.h>
#include <pic16f18854.h>
#include "motor.h"
#include "pwm.h"

void stop(void) {
    set_pwm(4, 0);
    set_pwm(1, 0);
    set_pwm(3, 0);
    set_pwm(2, 0);
}

void forward(void) {
    set_pwm(4, 255);
    set_pwm(1, 250);
    set_pwm(3, 0);
    set_pwm(2, 0);
}

void back(void) {
    set_pwm(4, 0);
    set_pwm(1, 0);
    set_pwm(3, 255);
    set_pwm(2, 255);
}

void turn_right(void) {
    set_pwm(4, 200);
    set_pwm(1, 0);
    set_pwm(3, 0);
    set_pwm(2, 0);
}

void turn_left(void) {
    set_pwm(4, 0);
    set_pwm(1, 200);
    set_pwm(3, 0);
    set_pwm(2, 0);
}

void forward_right(void) {
    set_pwm(4, 255);
    set_pwm(1, 200);
    set_pwm(3, 0);
    set_pwm(2, 0);
}

void forward_left(void) {
    set_pwm(4, 200);
    set_pwm(1, 250);
    set_pwm(3, 0);
    set_pwm(2, 0);
}