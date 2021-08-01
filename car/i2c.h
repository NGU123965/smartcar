#ifndef I2C_H
#define	I2C_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "pic16f18854.h"
#include <stdint.h>

void initIICCenterMode(void);
uint8_t* centerReadFromPeripheral(uint8_t peripheralAddr, uint8_t dataSize);
void centerWriteToPeripheral(uint8_t peripheralAddr, uint8_t* data, uint8_t dataSize);

uint8_t IIC_Read_Byte(uint8_t ack);
void IIC_Write_Byte(uint8_t d);
void IIC_ACK(uint8_t ack);
void IIC_Start(void);
void IIC_Stop(void);

#endif	/* XC_HEADER_TEMPLATE_H */

