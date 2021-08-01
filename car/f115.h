#ifndef F115
#define	F115

#include <xc.h> // include processor files - each processor file is guarded.
#include <pic.h>
#include "pic16f18854.h"

#define Pin_DAT PORTCbits.RC3

void F115_init(void);
void F115_send(unsigned char data);

void F115_header(void);
void F115_send_b1(void);
void F115_send_b0(void);
void F115_end(void);

#endif	/* XC_HEADER_TEMPLATE_H */

