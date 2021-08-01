#define _XTAL_FREQ 32000000UL

#include <xc.h>
#include <stdio.h>
#include "pic16f18854.h"
#include "i2c.h"
#include "mpu6050.h"
#include "eusart.h"
#include "util.h"
#include "control.h"


int8_t Ax, Ay, Az, Ax_abs, Ay_abs, Az_abs;
int Gx,Gy,Gz;

void MPU6050_Init()
{
    // Power-Up Delay & I2C_Init
    __delay_ms(100);

    // Setting The Sample (Data) Rate)
    uint8_t data[2] = {SMPLRT_DIV, 0x07};
    centerWriteToPeripheral(SIGNAL_PATH_RESET, data, 2);

    // Setting The Clock Source
    data[0] = PWR_MGMT_1;
    data[1] = 0x01;
    centerWriteToPeripheral(SIGNAL_PATH_RESET, data, 2);

    // Configure The DLPF
    data[0] = CONFIG;
    data[1] = 0x00;
    centerWriteToPeripheral(SIGNAL_PATH_RESET, data, 2);

    // Configure The ACCEL (FSR= +-2g)
    data[0] = ACCEL_CONFIG;
    data[1] = 0x00;
    centerWriteToPeripheral(SIGNAL_PATH_RESET, data, 2);

    // Configure The GYRO (FSR= +-2000d/s)
    data[0] = GYRO_CONFIG;
    data[1] = 0x18;
    centerWriteToPeripheral(SIGNAL_PATH_RESET, data, 2);

    // Enable Data Ready Interrupts
    data[0] = INT_ENABLE;
    data[1] = 0x01;
    centerWriteToPeripheral(SIGNAL_PATH_RESET, data, 2);
}

void MPU6050_Threshold_judgment() {
    Ax_abs = abs(Ax);
    Ay_abs = abs(Ay);
    Az_abs = abs(Az);
    if (Ax_abs > Ay_abs && Ax_abs > Az_abs) {
        if (Ax > 0) {
            forward();
        } else {
            back();
        }
    } else if (Az_abs > Ax_abs && Az_abs > Ay_abs) {
        if (Az > 0) {
            right();
        } else {
            left();
        }
    } else if (Ay_abs > Ax_abs && Ay_abs > Az_abs) {
        stop();
    }

    // if (Ay_abs > Ax_abs && Ay_abs > Az_abs) {
    //     stop();
    //     return;
    // }

    // if (Ax_abs > Ay_abs && Ax_abs > Az_abs && Ax < 0) {
    //     back();
    //     return;
    // }

    // if (Ax > 40) {
    //     if (Az_abs < 40) {
    //         forward();
    //         return;
    //     } else {
    //         if (Az > 0) {
    //             forward_right();
    //             return;
    //         } else {
    //             forward_left();
    //             return;
    //         }
    //     }
    // }

    // if (Az_abs > Ax_abs && Az_abs > Ay_abs) {
    //     if (Az > 0) {
    //         right();
    //         return;
    //     } else {
    //         left();
    //         return;
    //     }
    // }

}

void MPU6050_Read() {
    char buffer[40];
    
    uint8_t data[1] = {ACCEL_XOUT_H};
    centerWriteToPeripheral(SIGNAL_PATH_RESET, data, 1);

    uint8_t* rawDataFrame = centerReadFromPeripheral(SIGNAL_PATH_RESET, 14);
    // Ax = ((int)rawDataFrame[0]<<8) | (int)rawDataFrame[1];
    // Ay = ((int)rawDataFrame[2]<<8) | (int)rawDataFrame[3];
    // Az = ((int)rawDataFrame[4]<<8) | (int)rawDataFrame[5];
    Ax = rawDataFrame[0];
    Ay = rawDataFrame[2];
    Az = rawDataFrame[4];
    
    Gx = ((int)rawDataFrame[8]<<8) | (int)rawDataFrame[9];
    Gy = ((int)rawDataFrame[10]<<8) | (int)rawDataFrame[11];
    Gz = ((int)rawDataFrame[12]<<8) | (int)rawDataFrame[13];
    
    // // data visualizer数据可视化默认低位在前高位在后，故将数据高八位和第八位换位置
    // uint8_t frameToShow[14] = {rawDataFrame[1], rawDataFrame[0],rawDataFrame[3], rawDataFrame[2],rawDataFrame[5], rawDataFrame[4],rawDataFrame[7], rawDataFrame[6],rawDataFrame[9], rawDataFrame[8],rawDataFrame[11], rawDataFrame[10],rawDataFrame[13], rawDataFrame[12]};
    // transmitFrame(frameToShow, 14);
    
    //  sprintf(buffer,"Ax = %3d\t",Ax);
    //  transmitStr(buffer);
    //  sprintf(buffer," Ay = %3d\t",Ay);
    //  transmitStr(buffer);
    //  sprintf(buffer," Az = %3d\t",Az);
    //  transmitStr(buffer);
    //  sprintf(buffer," Gx = %3d\t",Gx);
    //  transmitStr(buffer);
    //  sprintf(buffer," Gy = %3d\t",Gy);
    //  transmitStr(buffer);
    //  sprintf(buffer," Gz = %3d\r\n",Gz);
    //  transmitStr(buffer);

}

