#include <stdlib.h>
#include "../include/list.h"
#include "../include/queue.h"

int queue_enqueue(Queue *queue, const void *data) {
    return list_insert(queue, list_tail(queue), data);
}

int queue_dequeue(Queue *queue) {
    return list_remove(queue, NULL);
}
