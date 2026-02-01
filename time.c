#include "time.h"
#include <time.h>

uint32_t get_system_time_ms(void) { return (uint32_t)(clock() * 1000 / CLOCKS_PER_SEC); }

void delay_ms(uint32_t ms) 
{
	clock_t start = clock();
	while ((uint32_t)((clock() - start) * 1000 / CLOCKS_PER_SEC) < ms);
}