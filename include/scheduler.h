#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>
#include "tasks.h"

bool scheduler_init(void);

bool add_task(rtos_task_t t);
void remove_task(int index);

void create_tasks(void);

void schedule();
rtos_task_t* pick_next_task(void);
rtos_task_t* get_current_task(void);

#endif