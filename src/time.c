#include "time.h"
#include <time.h>
#include <windows.h> // Change CPU freq calculations later so that this works on different OS
#include "../include/cpu.h"

#define UNIT 1000
#define TIME_CONVERSION 1000ULL

static uint64_t cpu_freq_hz = 0;

void init_time(void) 
{
	// To get the CPU's Frequency
	LARGE_INTEGER t1, t2, freq;
	uint64_t c1, c2;

	QueryPerformanceCounter(&t1);
	c1 = cpu_read_tsc();

	Sleep(100);
	QueryPerformanceCounter(&t2);
	c2 = cpu_read_tsc();

	QueryPerformanceFrequency(&freq);

	double seconds = (double)(t2.QuadPart - t1.QuadPart) / (double)freq.QuadPart;

	cpu_freq_hz = (uint64_t)((double)(c2 - c1) / seconds);
}

uint64_t get_system_time_ms(void) 
{ 
	uint64_t cycles = cpu_read_tsc(); // Cycles
	return cycles / (cpu_freq_hz / 1000ULL);
}

void delay_ms(uint32_t ms) 
{
	clock_t start = clock();
	while ((uint32_t)((clock() - start) * UNIT / CLOCKS_PER_SEC) < ms);
}