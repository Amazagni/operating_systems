#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <time.h>

int waiting = 1;
int task = -1;
int tasksCount = 0;
clock_t start;
clock_t end;
int counter = 0;

void printNumbers() {
    for (int j = 1; j <= 100; j++) {
        printf("%d ", j);
    }
    printf("\n");
}

void printCurrentTime() {
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Current time: %s", asctime(timeinfo));
}

void printTasksCount() {
    printf("Current task count: %d\n", tasksCount);
}



void handler(int signo, siginfo_t* info, void* context) {
    waiting = 1;
    task = info->si_status;
    printf("CATCHER: RECEIVED SIGNAL %d\n", task);
    switch (task) {
        case 1:
            tasksCount += 1;
            printNumbers();
            break;
        case 2:
            tasksCount += 1;
            printCurrentTime();
            break;
        case 3:
            tasksCount += 1;
            printTasksCount();
            break;
        case 4:
            tasksCount += 1;
            start = clock();
            counter = 0;
            waiting = 0;
            break;
        case 5:
            kill(info->si_pid, SIGUSR1);
            exit(0);
        default:
            perror("Wrong argument\n");
    }
    kill(info->si_pid, SIGUSR1);
}

int main(int argc, char *argv[]) {
    printf("CATCHER PID = %d\n", getpid());
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handler;
    sigaction(SIGUSR1, &act,NULL);
    while (true) {
        if (waiting == 0) {
            end = clock();
            if ((double)(end - start) / CLOCKS_PER_SEC > counter) {
                counter += 1;
                printCurrentTime();
            }
        }
    }

    return 0;
}