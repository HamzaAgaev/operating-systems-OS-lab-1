#include "benchmark-2.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

static int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

void benchmark2() {
    FILE *inputFile;
    FILE *outputFile;
    inputFile = fopen(INPUT_FILENAME, "r");

    int numbersCount;
    fscanf(inputFile, "%d", &numbersCount);

    int *inputNumbers = (int *) malloc(numbersCount * sizeof(int));
    for (int i = 0; i < numbersCount; i++) {
        fscanf(inputFile, "%d", &inputNumbers[i]);
    }
    qsort(inputNumbers, numbersCount, sizeof(int), compare);

    char fileNamePrefix[GEN_STR_LEN + 1];
    generateRandomString(fileNamePrefix, GEN_STR_LEN + 1);
    char outputFileName[MAX_FILENAME_LEN];
    snprintf(outputFileName, sizeof(outputFileName), OUTPUT_FILENAME_FORMAT, fileNamePrefix);
    outputFile = fopen(outputFileName, "w");
    for (int i = 0; i < numbersCount; i++) {
        if (i == 0 || inputNumbers[i] != inputNumbers[i - 1]) {
            fprintf(outputFile, "%d ", inputNumbers[i]);
        }
    }
    free(inputNumbers);
}
