#ifndef TIME_H
#define TIME_H

#include <stdint.h>

uint64_t get_system_time_ms(void);
void delay_ms(uint32_t ms);
void init_time(void);

#endif