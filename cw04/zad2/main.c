#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

int signalNumber = 1;
int c = 1, dep = 1;
void handler(int sigNo, siginfo_t* info, void* _) {
    printf("PID: %d, SIG_NO: %d, STATUS: %d, UID: %d, SIG VAL: %d \n",
           info->si_pid, info->si_signo,info->si_status, info->si_uid, info->si_value.sival_int);
    signalNumber += 1;
}

void testSiginfo(struct sigaction act) {
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act,NULL);
    printf("Parent: ");
    kill(getpid(), SIGUSR1);

    if (fork() == 0) {
        printf("Child: ");
        kill(getpid(),SIGUSR1);
        exit(0);
    }
    else {
        wait(NULL);
    }
}


void handlerND(int sigNo, siginfo_t* info, void* _) {
    printf("[In handler] id:%d depth:%d\n",c,dep);
    c += 1;
    dep += 1;
    if (c < 5) {
        kill(getpid(),SIGUSR1);
    }
    dep -= 1;
}

void testResetHandler(struct sigaction act) {
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESETHAND;
    act.sa_sigaction = handlerND;
    sigaction(SIGUSR1, &act,NULL);
    printf("First usage: ");
    kill(getpid(),SIGUSR1);
    printf("Second usage: ");
    kill(getpid(),SIGUSR1);
}

void testNoDefer(struct sigaction act) {
    printf("WITH SA_NODEFER \n");
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handlerND;
    act.sa_flags = SA_NODEFER;
    sigaction(SIGUSR1, &act,NULL);
    kill(getpid(), SIGUSR1);

    printf("WITHOUT SA_NODEFER \n");
    c = 1;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act,NULL);
    kill(getpid(),SIGUSR1);
}

void test(struct sigaction act) {
    printf("SA_SIGINFO\n");
    testSiginfo(act);
    printf("\nSA_NODEFER\n");
    testNoDefer(act);
    printf("\nSA_RESETHAND\n");
    testResetHandler(act);
}

int main() {
    struct sigaction act;
    test(act);
    return 0;
}