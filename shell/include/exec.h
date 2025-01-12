#ifndef OS_LAB_1_EXEC_H
#define OS_LAB_1_EXEC_H

typedef struct {
    double execTimeInSec;
    int statusCode;
} ExecResult;

ExecResult ExecCommand(char *args[]);

#endif // OS_LAB_1_EXEC_H
