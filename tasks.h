#pragma once

#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef enum {
	TASK_READY,
	TASK_RUNNING,
	TASK_BLOCKED
} task_state_t;

typedef struct {
	void (*task_fn)(void*);
	void* arg;
	uint32_t period_ms;
	uint32_t next_release;
	uint8_t priority;
	task_state_t state;
} rtos_task_t;

#endif