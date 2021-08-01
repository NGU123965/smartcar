#ifndef LED_H
#define	LED_H

#include <xc.h>
#include <stdint.h>
#include "pic16f18854.h"

void LED_ON(uint8_t led_num);
void LED_ALL_ON(void);
void LED_ALL_OFF(void);
void LED_3_OFF(void);

#endif	/* LED_H */

