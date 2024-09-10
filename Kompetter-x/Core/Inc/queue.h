#ifndef QUEUE_H
#define QUEUE_H

#include "OledDisplayManager.h"  // Include this for the Scene type

typedef struct Node {
    Scene data;
    struct Node* next;
} Node;

typedef struct {
    uint8_t front, rear, size;
    unsigned capacity;
    Scene* array;
} Queue;

void queueInit(Queue* q, uint8_t capacity);
uint8_t queueIsEmpty(Queue* q);
void queueEnqueue(Queue* q, Scene data);
Scene queueDequeue(Queue* q);
uint8_t queueIsFull(Queue* q);

#endif // QUEUE_H
