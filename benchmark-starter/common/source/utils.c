#include "../include/utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

static bool isRandomInitialized = false;

static void initializeRandom() {
    srand((unsigned int) time(NULL));
    isRandomInitialized = true;
}

void generateRandomString(char *str, int length) {
    if (!isRandomInitialized) {
        initializeRandom();
    }
    char start = 'a';
    char end = 'z';
    int range = end - start + 1;

    for (int i = 0; i < length - 1; i++) {
        str[i] = (char) (start + (char) (rand() % range));
    }

    str[length - 1] = '\0';
}