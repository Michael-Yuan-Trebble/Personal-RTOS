#include "mutex.h"
#include "include/scheduler.h"
#include "include/tasks.h"

#define LOG(fmt, ...) \
    printf("[%lu] " fmt "\n", get_system_time_ms(), ##__VA_ARGS__)

int shared = 0;
mutex_t m;

void taskA(void* arg) {
	static int state = 0;
	switch (state) {
	case 0: {
		LOG("A: try lock");
		mutex_lock(&m);
		if (m.owner != get_current_task()) return;
		LOG("A: locked");
		state = 1;
		return;
	}

	case 1: {
			int tmp = shared;
			tmp++;
			shared = tmp;
			LOG("A: shared = %d", shared);
			mutex_unlock(&m);
			LOG("A: unlock");
			state = 0;
			return;
		}
	}
}