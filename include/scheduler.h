#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>
#include "tasks.h"

bool scheduler_init(void);

bool add_task(rtos_task_t t);
void remove_task(int index);

void schedule();
rtos_task_t* pick_next_task(void);

#endif