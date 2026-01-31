#include "scheduler.h"
#include <time.h>
#include "time.h"

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
	uint32_t time = get_system_time_ms();
	rtos_task_t* execute = NULL;
	for (int i = 0; i < task_count; i++) 
	{
		if (!tasks_ready[i]) continue;
		if (tasks[i].state != TASK_READY) continue;
		if (get_system_time_ms() < tasks[i].next_release) continue;
		if (!execute) execute = &tasks[i];
		else execute = tasks[i].priority > execute->priority ? &tasks[i].priority : execute->priority;
		execute->next_release += execute->period_ms;
	}
	if (execute) execute->task_fn(execute->arg);
}