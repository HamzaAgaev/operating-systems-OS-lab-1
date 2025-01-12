#include "benchmark-1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file-state.h"
#include "heap-lib.h"
#include "utils.h"

#define MEMORY_COEFFICIENT 16

static int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

static int ceilDiv(int a, int b) {
    return a / b + (a % b != 0);
}

void benchmark1() {
    FILE *inputFile;
    FILE *outputFile;
    inputFile = fopen(INPUT_FILENAME, "r");

    int numbersCount;
    fscanf(inputFile, "%d", &numbersCount);

    int blockSize = numbersCount / MEMORY_COEFFICIENT;
    int *block = (int *) malloc(blockSize * sizeof(int));

    int filesCount = ceilDiv(numbersCount, blockSize);
    char fileNames[filesCount][MAX_FILENAME_LEN];

    char fileNamePrefix[GEN_STR_LEN + 1];
    generateRandomString(fileNamePrefix, GEN_STR_LEN + 1);

    for (int i = 0; i < numbersCount; i++) {
        fscanf(inputFile, "%d", &block[i % blockSize]);
        if ((i != 0 && (i + 1) % blockSize == 0) || i == numbersCount - 1) {
            char tempFileName[MAX_FILENAME_LEN];
            int fileIndex = ceilDiv((i + 1), blockSize) - 1;
            snprintf(tempFileName, sizeof(tempFileName), TEMP_FILENAME_FORMAT, fileNamePrefix, fileIndex);
            memcpy(fileNames[fileIndex], tempFileName, sizeof(tempFileName));
            FILE *tempFile = fopen(tempFileName, "w");

            int nel;
            if ((i + 1) % blockSize == 0) {
                nel = blockSize;
            } else {
                nel = numbersCount % blockSize;
            }
            qsort(block, nel, sizeof(int), compare);
            for (int j = 0; j < nel; j++) {
                fprintf(tempFile, "%d ", block[j]);
            }
            fclose(tempFile);
        }
    }
    free(block);
    fclose(inputFile);

    FileState fileStates[filesCount];

    for (int i = 0; i < filesCount; i++) {
        initializeFileState(&fileStates[i], fileNames[i]);
    }

    PriorityQueue *pq = newPriorityQueue(filesCount);
    for (int i = 0; i < filesCount; i++) {
        if (!fileStates[i].isEndOfFile) {
            offer(pq, fileStates[i]);
        }
    }

    char outputFileName[MAX_FILENAME_LEN];
    snprintf(outputFileName, sizeof(outputFileName), OUTPUT_FILENAME_FORMAT, fileNamePrefix);
    outputFile = fopen(outputFileName, "w");
    fprintf(outputFile, "%d\n", numbersCount);

    while (!isEmpty(pq)) {
        FileState fileState = poll(pq);
        fprintf(outputFile, "%d ", fileState.value);
        updateFileState(&fileState);
        if (!fileState.isEndOfFile) {
            offer(pq, fileState);
        }
    }

    for (int i = 0; i < filesCount; i++) {
        closeFileState(&fileStates[i]);
        remove(fileNames[i]);
    }
    freePriorityQueue(pq);
    fclose(outputFile);
}
