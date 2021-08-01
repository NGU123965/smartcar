#ifndef SYN480R
#define	SYN480R

# include <stdint.h>

void init_syn480r(void);
uint8_t get_raw_signal(void);
void handle_wireless_control(void);

#endif