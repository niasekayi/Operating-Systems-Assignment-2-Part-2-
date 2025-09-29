#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void child_process() {
    int parent_pid = getppid();
    int pid = getpid();

    int n = 1 + (random() % 30);

    for (int i = 0; i < n; i++) {
        int time = 1 + (random() % 10); 
        printf("Child Pid: %d is going to sleep for %d seconds!\n", pid, time);
        sleep(time);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", pid, parent_pid);
    }

    exit(0);
}

int main() {
    srandom(time(NULL));
    int pid;

    for (int i = 0; i < 2; i++) {
        pid = fork();
        if (pid == 0) {
            child_process(); 
        } else if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
    }

    for (int i = 0; i < 2; i++) {
        int status;
        int completed_pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Child Pid: %d has completed with exit status: %d\n",
                    completed_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
