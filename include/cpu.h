#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t cpu_read_tsc(void);
uint64_t cpu_get_sp(void);
void cpu_pause(void);

#ifdef __cplusplus
}
#endif
#endif