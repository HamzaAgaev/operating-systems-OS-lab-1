#ifndef OS_LAB_1_HEAP_LIB_H
#define OS_LAB_1_HEAP_LIB_H

#include <stdbool.h>
#include <stdlib.h>

#include "file-state.h"

typedef struct {
    FileState *data;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue *newPriorityQueue(int capacity);

void freePriorityQueue(PriorityQueue *pq);

bool isEmpty(PriorityQueue *pq);

void offer(PriorityQueue *pq, FileState value);

FileState peek(PriorityQueue *pq);

FileState poll(PriorityQueue *pq);

#endif // OS_LAB_1_HEAP_LIB_H
