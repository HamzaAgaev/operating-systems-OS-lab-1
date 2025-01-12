#include "file-state.h"

void initializeFileState(FileState *fileState, const char *filename) {
    fileState->file = fopen(filename, "rb");
    fileState->isEndOfFile = false;
    if (fscanf(fileState->file, "%d", &fileState->value) != 1) {
        fileState->isEndOfFile = true;
    }
}

void updateFileState(FileState *fileState) {
    if (fscanf(fileState->file, "%d", &fileState->value) != 1) {
        fileState->isEndOfFile = true;
    }
}

void closeFileState(FileState *fileState) {
    fclose(fileState->file);
}
