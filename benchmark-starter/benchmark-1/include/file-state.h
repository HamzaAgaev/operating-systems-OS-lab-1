#ifndef OS_LAB_1_FILE_STATE_H
#define OS_LAB_1_FILE_STATE_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {
    FILE *file;
    int value;
    bool isEndOfFile;
} FileState;

void initializeFileState(FileState *fileState, const char *filename);

void updateFileState(FileState *fileState);

void closeFileState(FileState *fileState);

#endif // OS_LAB_1_FILE_STATE_H
