#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


int waiting = 0;

void handler(int signo, siginfo_t* info, void* context) {
    waiting = 0;
    return;
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("Invalid number of arguments\n");
        return 0;
    }
    int cpid = atoi(argv[1]);
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handler;
    sigaction(SIGUSR1, &act,NULL);

    for (int i = 2; i < argc; i++) {
        int task = atoi(argv[i]);
        sigval_t val = {task};
        sigqueue(cpid, SIGUSR1, val);
        waiting = 1;
        while (waiting == 1) {}
    }


    return 0;
}
