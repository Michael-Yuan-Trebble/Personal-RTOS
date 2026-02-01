#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>
#include "tasks.h"

bool add_task(rtos_task_t t);
void remove_task(int index);

void schedule();

#endif