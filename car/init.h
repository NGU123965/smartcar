#ifndef INIT_H
#define	INIT_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "pic16f18854.h"


void init_hardware(void);
void init_tmr0(void);
void reset_tmr0(void);

#endif	/* XC_HEADER_TEMPLATE_H */

