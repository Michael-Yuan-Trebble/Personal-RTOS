#include "mutex.h"
#include "include/scheduler.h"

void mutex_init(mutex_t* m) {
	m->owner = NULL;
	m->locked = 0;
}

void mutex_lock(mutex_t* m) {
	rtos_task_t* current_task = get_current_task();
	if (!m || !current_task) return;

	if (!m->locked) {
		m->locked = 1;
		m->owner = get_current_task();
		return;
	}
	if (!m->owner) return;
	if (current_task->priority > m->owner->priority) {
		m->owner->priority = current_task->priority;
	}

	m->wait_list[m->wait_count++] = current_task;
	set_task_block_forever(current_task);
}

void mutex_unlock(mutex_t* m) {
	rtos_task_t* current_task = get_current_task();
	if (!m || !m->owner || !current_task || m->owner != current_task) return;

	if (m->wait_count > 0) {
		int best = 0;
		for (int i = 1; i < m->wait_count; i++) {
			if (m->wait_list[i]->priority > m->wait_list[best]->priority) best = i;
		}
		rtos_task_t* next = m->wait_list[best];

		for (int i = best; i < m->wait_count - 1; i++) {
			m->wait_list[i] = m->wait_list[i + 1];
		}
		m->wait_count--;

		m->owner = next;
		task_unblock(next);
		set_task_ready(next);
	}
	else {
		m->locked = 0;
		m->owner = NULL;
	}
	current_task->priority = current_task->base_priority;
}
