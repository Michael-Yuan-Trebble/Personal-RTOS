#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include "tasks.h"

typedef struct {
	uint8_t* buffer;
	uint16_t item_size;
	uint16_t length;

	uint8_t head;
	uint8_t tail;
	uint8_t count;

	rtos_task_t* waiting_send;
	rtos_task_t* waiting_recv;
}queue;

bool queue_send(queue* inQ, const void* item, uint32_t timeout_ms, uint32_t now);
bool queue_receive(queue* inQ, void* out_item, uint32_t timeout_ms, uint32_t now);
void queue_copy_in(queue* q, const void* item);
void queue_copy_out(queue* q, void* out_item);
bool queue_is_full(queue* q);
bool queue_is_empty(queue* q);

#endif