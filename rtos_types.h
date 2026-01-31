#ifndef RTOS_TYPES_H
#define RTOS_TYPES_H

typedef enum {
	READY = 1 << 0,
	FAULT = 1 << 1,
	TIMEOUT = 1 << 2
} flags_t;

typedef enum {
	ready,
	blocked,
	run
} state_t;

#endif