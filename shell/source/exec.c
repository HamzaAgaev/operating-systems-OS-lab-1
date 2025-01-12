#include "exec.h"

#include <errno.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define NANOSEC_IN_SEC 1e9

ExecResult ExecCommand(char *args[]) {
    pid_t pid = vfork();
    ExecResult result = {.execTimeInSec = 0, .statusCode = 0};
    if (pid <= -1) {
        result.statusCode = errno;
        result.execTimeInSec = 0;
    } else if (pid == 0) {
        int exec_code = execvp(args[0], args);
        int error_code = exec_code == 0 ? 0 : errno;
        _exit(error_code);
    } else {
        struct timespec start;
        struct timespec end;
        int stat_loc;
        clock_gettime(CLOCK_MONOTONIC, &start);
        waitpid(pid, &stat_loc, 0);
        clock_gettime(CLOCK_MONOTONIC, &end);
        if (WIFEXITED(stat_loc)) {
            result.statusCode = WEXITSTATUS(stat_loc);
        } else if (WIFSIGNALED(stat_loc)) {
            result.statusCode = WTERMSIG(stat_loc);
        } else {
            result.statusCode = 0;
        }
        double exec_time_in_sec =
                (double) (end.tv_sec - start.tv_sec) + ((double) (end.tv_nsec - start.tv_nsec) / NANOSEC_IN_SEC);
        result.execTimeInSec = exec_time_in_sec;
    }
    return result;
}
