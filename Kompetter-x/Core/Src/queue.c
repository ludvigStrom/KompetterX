#include "queue.h"
#include <stdlib.h>  // Include this for malloc and free

void queueInit(Queue* queue, uint8_t capacity) {
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;
	queue->array = (Scene*) malloc(queue->capacity * sizeof(Scene));
}

uint8_t queueIsEmpty(Queue* queue) {
    return (queue->size == 0);
}

void queueEnqueue(Queue* queue, Scene item) {
    if (queueIsFull(queue)) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

Scene queueDequeue(Queue* q) {
    Scene data;

    if (q->front != NULL) {
        Node* frontNode = q->front;
        data = frontNode->data;
        q->front = frontNode->next;

        if (q->front == NULL) {
            q->rear = NULL;
        }

        free(frontNode);
    }

    return data;
}

uint8_t queueIsFull(Queue* queue) {
    return (queue->size == queue->capacity);
}
