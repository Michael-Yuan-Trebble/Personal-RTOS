#ifndef MUTEX_H
#define MUTEX_H

#include "include/tasks.h"
#define MAX_TASKS 16

typedef struct {
	rtos_task_t* owner;
	rtos_task_t* wait_list[MAX_TASKS];
	uint8_t wait_count;
	uint8_t locked;
} mutex_t;

void mutex_init(mutex_t* m);
void mutex_lock(mutex_t* m);
void mutex_unlock(mutex_t* m);

#endif