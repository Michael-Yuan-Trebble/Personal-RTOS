#include "../include/cpu.h"

extern uint64_t asm_read_tsc(void);
extern uint64_t asm_get_sp(void);
extern void asm_pause(void);

uint64_t cpu_read_tsc(void) {
	return asm_read_tsc();
}

uint64_t cpu_get_sp(void) {
	return asm_get_sp();
}

void cpu_pause(void) {
	asm_pause();
}