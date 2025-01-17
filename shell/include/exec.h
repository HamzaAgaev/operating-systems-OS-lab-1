#ifndef OS_LAB_1_EXEC_H
#define OS_LAB_1_EXEC_H

typedef struct {
    double execTimeInSeconds;
    int statusCode;
} ExecResult;

ExecResult execCommand(char *args[]);

#endif // OS_LAB_1_EXEC_H
