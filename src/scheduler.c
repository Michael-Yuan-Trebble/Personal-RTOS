#include "../include/scheduler.h"
#include <time.h>
#include <stdio.h>
#include "time.h"
#include "../include/cpu.h"

#define MAX_TASKS 16

// Currently Static, check actual RTOS implementation if it remains static or is dynamic
rtos_task_t tasks[MAX_TASKS];
bool tasks_ready[MAX_TASKS] = { 0 };
int task_count = 0;

bool scheduler_init(void) {
	init_time();
	return true;
}

// Add task to the first index that is available, return true if can
bool add_task(rtos_task_t t) 
{
	for (int i = 0; i < task_count; i++) 
	{
		if (!tasks_ready[i]) 
		{
			tasks[i] = t;
			tasks_ready[i] = true;
			return true;
		}
	}
	return false;
}

void remove_task(int index) { tasks_ready[index] = false; }

// Main loop running all the tasks
void schedule()
{
	uint32_t now = get_system_time_ms();
	printf("now: %lu\n", now);
	uint32_t time = get_system_time_ms();
	rtos_task_t* execute = NULL;
	for (int i = 0; i < task_count; i++) 
	{
		if (!tasks_ready[i]) continue;
		if (tasks[i].state != TASK_READY) continue;
		if (get_system_time_ms() < tasks[i].next_release) continue;
		if (execute == NULL) execute = &tasks[i];
		else execute = tasks[i].priority > execute->priority ? &tasks[i] : execute;
	}
	if (execute != NULL) {
		execute->task_fn(execute->arg);
		task_set_next_release(execute, time);
	}
}