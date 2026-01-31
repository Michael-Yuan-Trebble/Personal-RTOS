#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>
#include "tasks.h"

#define MAX_TASKS 16

// Currently Static, check actual RTOS implementation if it remains static or is dynamic
rtos_task_t tasks[MAX_TASKS];
bool tasks_ready[MAX_TASKS] = { 0 };
int task_count = 0;

bool add_task(rtos_task_t t);
void remove_task(int index);

void schedule();

#endif