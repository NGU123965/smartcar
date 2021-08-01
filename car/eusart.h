/* 
 * File:   eusart.h
 * Author: holdice
 *
 * Created on 2021年6月22日, 下午8:00
 */

#include "xc.h"
#include "pic16f18854.h"

void init_EUSART(void);
void transmitData(unsigned char);
void transmitStr(char*);
void transmitFrame(uint8_t* frame, uint8_t dataSize);

