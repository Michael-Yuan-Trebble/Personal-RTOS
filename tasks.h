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

void task_init(
	rtos_task_t* task,
	void (*fn)(void*),
	void* arg,
	uint32_t period_ms,
	uint8_t priority
);

void set_task_block(rtos_task_t* task);

void set_task_ready(rtos_task_t* task);

void task_set_next_release(rtos_task_t* task, uint32_t now);

int task_is_ready(const rtos_task_t* task, uint32_t now);

void task_delay(rtos_task_t* task, uint32_t delay_ms, uint32_t now);

void task_mark_start(rtos_task_t* task, uint32_t now);

void task_mark_end(rtos_task_t* task, uint32_t now);

int task_deadline_missed(const rtos_task_t* task, uint32_t now);

#endif