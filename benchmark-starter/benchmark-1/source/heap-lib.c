#include "heap-lib.h"

#include <stdlib.h>

#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)

static void resize(PriorityQueue *pq) {
    pq->capacity *= 2;
    pq->data = (FileState *) realloc(pq->data, pq->capacity * sizeof(FileState));
}

static void swap(FileState *a, FileState *b) {
    FileState temp = *a;
    *a = *b;
    *b = temp;
}

PriorityQueue *newPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    pq->data = (FileState *) malloc(capacity * sizeof(FileState));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void freePriorityQueue(PriorityQueue *pq) {
    free(pq->data);
    free(pq);
}

bool isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

void offer(PriorityQueue *pq, FileState value) {
    if (pq->size == pq->capacity) {
        resize(pq);
    }
    pq->data[pq->size] = value;
    int i = pq->size;
    pq->size++;

    // heapify
    while (i != 0 && pq->data[PARENT(i)].value > pq->data[i].value) {
        swap(&pq->data[PARENT(i)], &pq->data[i]);
        i = PARENT(i);
    }
}

FileState peek(PriorityQueue *pq) {
    // no isEmpty(pq) check
    return pq->data[0];
}

FileState poll(PriorityQueue *pq) {
    // no isEmpty(pq) check
    FileState root = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;

    // heapify
    int i = 0;
    while (true) {
        int left = LEFT(i);
        int right = RIGHT(i);
        int smallest = i;

        if (left < pq->size && pq->data[left].value < pq->data[smallest].value) {
            smallest = left;
        }
        if (right < pq->size && pq->data[right].value < pq->data[smallest].value) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        swap(&pq->data[i], &pq->data[smallest]);
        i = smallest;
    }

    return root;
}
