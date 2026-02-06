#include "../include/scheduler.h"
#include <time.h>
#include <stdio.h>
#include "../mutex.h"
#include "../include/cpu.h"
#include "../taskA.h"

#define MAX_TASKS 16
rtos_task_t* current_task = NULL;
mutex_t m;

// Currently Static, check actual RTOS implementation if it remains static or is dynamic
rtos_task_t tasks[MAX_TASKS];
bool tasks_ready[MAX_TASKS] = { 0 };
int task_count = 0;

bool scheduler_init(void) {
	init_time();
	return true;
}

void create_tasks(void) {
	mutex_init(&m);
	rtos_task_t* t = &tasks[task_count++];
	t->task_fn = taskA;
	t->arg = NULL;
	t->priority = 2;
	t->base_priority = 2;
	t->state = TASK_READY;
	t->next_release = 0;
	tasks_ready[0] = true;
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

rtos_task_t* pick_next_task(void) {
	rtos_task_t* next = NULL;
	for (int i = 0; i < task_count; i++) {
		if (!tasks_ready[i]) continue;
		if (tasks[i].state != TASK_READY) continue;
		if (get_system_time_ms() < tasks[i].next_release) continue;

		if (!next || tasks[i].priority > next->priority) next = &tasks[i];
	}
	return next;
}

// Main loop running all the tasks
void schedule()
{
	uint32_t now = get_system_time_ms();
	//printf("now: %lu\n", now);
	uint32_t time = get_system_time_ms();
	rtos_task_t* execute = pick_next_task();

	if (execute != NULL) {
		current_task = execute;
		execute->task_fn(execute->arg);
		task_set_next_release(execute, time);
	}
	else {
		cpu_halt();
	}
}

rtos_task_t* get_current_task(void) {
	return current_task;
}