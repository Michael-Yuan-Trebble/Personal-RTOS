#include "tasks.h"

uint32_t task_start = 0;
uint32_t task_end = 0;

void task_init(
	rtos_task_t* task,
	void (*fn)(void*),
	void* arg,
	uint32_t period_ms,
	uint8_t priority
) {
	if (task == NULL) return;
	task->task_fn = fn;
	task->arg = arg;
	task->period_ms = period_ms;
	task->priority = priority;
	task->next_release = 0;
	task->state = TASK_READY;
}

void task_delay(rtos_task_t* task, uint32_t delay_ms, uint32_t now) {
	if (task == NULL) return;
	task->state = TASK_BLOCKED;
	task->next_release = now + delay_ms;
}

void task_mark_start(rtos_task_t* task, uint32_t now) {
	if (task == NULL) return;
	task_start = now;
}

void task_mark_end(rtos_task_t* task, uint32_t now) {
	if (task == NULL) return;
	task_end = now;
}

int task_deadline_missed(const rtos_task_t* task, uint32_t now) 
{
	if (task == NULL) return -1;
	return 0;
}

void set_task_block(rtos_task_t* task) { if (task) task->state = TASK_BLOCKED; }

void set_task_ready(rtos_task_t* task) { if(task) task->state = TASK_READY; }

void task_set_next_release(rtos_task_t* task, uint32_t now) { if(task) task->next_release = now + task->period_ms; }

int task_is_ready(const rtos_task_t* task, uint32_t now) { if (!task) return -1; else return (task->state == TASK_READY) && (now >= task->next_release); }