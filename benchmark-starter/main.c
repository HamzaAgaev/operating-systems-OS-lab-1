#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "benchmark-1/include/benchmark-1.h"
#include "benchmark-2/include/benchmark-2.h"

void *threadB1Function(void *arg) {
    benchmark1();
    return NULL;
}

void *threadB2Function(void *arg) {
    benchmark2();
    return NULL;
}

int main() {
    int threadsB1Count, threadsB2Count;
    fprintf(stdout, "Enter count of thread for benchmark-1: ");
    fscanf(stdin, "%d", &threadsB1Count);
    fprintf(stdout, "Enter count of thread for benchmark-2: ");
    fscanf(stdin, "%d", &threadsB2Count);

    pthread_t *threadsB1 = malloc(threadsB1Count * sizeof(pthread_t));
    pthread_t *threadsB2 = malloc(threadsB2Count * sizeof(pthread_t));
    int *threadB1Ids = malloc(threadsB1Count * sizeof(int));
    int *threadB2Ids = malloc(threadsB2Count * sizeof(int));

    for (int i = 0; i < threadsB1Count; i++) {
        threadB1Ids[i] = i;
        pthread_create(&threadsB1[i], NULL, threadB1Function, &threadB1Ids[i]);
    }
    for (int i = 0; i < threadsB2Count; i++) {
        threadB2Ids[i] = i;
        pthread_create(&threadsB2[i], NULL, threadB2Function, &threadB2Ids[i]);
    }

    for (int i = 0; i < threadsB1Count; i++) {
        pthread_join(threadsB1[i], NULL);
    }
    for (int i = 0; i < threadsB2Count; i++) {
        pthread_join(threadsB2[i], NULL);
    }

    free(threadsB1);
    free(threadsB2);
    free(threadB1Ids);
    free(threadB2Ids);
}