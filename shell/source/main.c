#include <stdio.h>
#include <string.h>

#include "exec.h"

#define MAX_ARGS 100
#define MAX_COMMAND_LENGTH 100

void printNewLine() {
    fprintf(stdout, "\n");
}

int main() {
    const char inputTextFormat[] = "shell >> ";
    const char execTextFormat[] = "\033[32mExec time: %f\033[0m\n";
    const char errorTextFormat[] = "\033[31mError code: %d\033[0m\n";
    const char exitText[] = "exit";
    const char delimiter[] = " ";
    char entered_command[MAX_COMMAND_LENGTH];
    do {
        fprintf(stdout, inputTextFormat);
        if (fgets(entered_command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            break;
        }
        size_t len = strlen(entered_command);
        if (len > 0 && entered_command[len - 1] == '\n') {
            entered_command[len - 1] = '\0';
        }
        char *command_args[MAX_ARGS + 1];
        int args_count = 0;
        char *arg = strtok(entered_command, delimiter);
        while (arg != NULL && args_count < MAX_ARGS) {
            command_args[args_count] = arg;
            args_count++;
            arg = strtok(NULL, delimiter);
        }
        if (strcmp(command_args[0], exitText) == 0) {
            break;
        }
        command_args[args_count + 1] = NULL;
        ExecResult result = ExecCommand(command_args);
        fprintf(stdout, execTextFormat, result.execTimeInSec);
        if (result.statusCode != 0) {
            fprintf(stdout, errorTextFormat, result.statusCode);
        }
        printNewLine();
    } while (1);
    return 0;
}
