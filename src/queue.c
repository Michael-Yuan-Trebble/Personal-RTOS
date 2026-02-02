#include "../include/queue.h"
#include <string.h>

bool queue_send(queue* q, const void* item, uint32_t timeout_ms, uint32_t now) 
{
    if (q == NULL ||item == NULL) return false;
    // not using values as of now
    (void)timeout_ms;
    (void)now;

    if (queue_is_full(q)) {
        return false;
    }

    queue_copy_in(q, item);
    if (q->waiting_recv != NULL) {
        q->waiting_recv->state = TASK_READY;
        q->waiting_recv = NULL;
    }

    return true;
}

bool queue_receive(queue* q, void* out_item, uint32_t timeout_ms, uint32_t now) 
{
    if (q == NULL || out_item == NULL) return false;

    if (queue_is_empty(q)) return false;

    (void)timeout_ms;
    (void)now;

    queue_copy_out(q, out_item);

    return true;
}

bool queue_is_full(queue* q) { if (q) return q->count >= q->length; else return false; }

bool queue_is_empty(queue* q) { if (q) return q->count <= 0; else return false; }

void queue_copy_in(queue* q, const void* item) 
{
    if (q == NULL || item == NULL) return;
    uint8_t* dest = q->buffer + (q->head * q->item_size);
    memcpy(dest, item, q->item_size);

    q->head = (q->head + 1) % q->length;
    q->count++;
}

void queue_copy_out(queue* q, void* out_item) 
{
    if (q == NULL || out_item == NULL) return;
    uint8_t* src = q->buffer + (q->tail * q->item_size);
    memcpy(out_item, (const void*)src, q->item_size);

    q->tail = (q->tail + 1) % q->length;
    q->count--;
}