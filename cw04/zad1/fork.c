#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void testIgnore(){
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    signal(SIGUSR1, SIG_IGN);
    raise(SIGUSR1);
    printf("Parent: Ignore test passed\n");
    pid_t child_pid = fork();
    if(child_pid == 0){
        raise(SIGUSR1);
        printf("Child: Ingore test passed\n");
        exit(0);
    }
    wait(NULL);
}

void handler(){
    printf("Handler test passed\n");
}

void testHandler(){
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    signal(SIGUSR1, handler);
    printf("Parent: ");
    raise(SIGUSR1);
    pid_t child_pid = fork();
    if(child_pid == 0){
        printf("Child: ");
        raise(SIGUSR1);
        exit(0);
    }
    wait(NULL);
}


void testMask(){
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, NULL);
    raise(SIGUSR1);
    printf("Parent: Mask test passed\n");
    pid_t child_pid = fork();
    if(child_pid == 0){
        raise(SIGUSR1);
        printf("Child: Mask test passed\n");
        exit(0);
    }
    wait(NULL);
}

void testPending(){
    sigset_t set, parentPending;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, NULL);
    raise(SIGUSR1);
    sigpending(&parentPending);


    if(sigismember(&parentPending, SIGUSR1)){
        printf("Parent: SIGUSR1 pending ...\n");
    }

    pid_t child_pid = fork();
    if(child_pid == 0){
        sigset_t childPending;
        sigpending(&childPending);
        if(sigismember(&childPending, SIGUSR1)){
            printf("Child: SIGUSR1 pending ...\n");
        }
        else{
            printf("Child: SIGUSR1 not pending\n");
        }
        exit(0);
    }
    wait(NULL);
}


void test (char* arg){
    if(strcmp(arg, "ignore") == 0){
        testIgnore();
        return;
    }
    if(strcmp(arg, "handler") == 0){
        testHandler();
        return;
    }
    if(strcmp(arg, "mask") == 0){
        testMask();
        return;
    }
    if(strcmp(arg, "pending") == 0){
        testPending();
        return;
    }
    printf("Incorrect argument: ignore / handler / mask / pending\n");
    return;
}

int main(int argc, char* argv[]) {

    if(argc != 2){
        printf("One argument required (ignore / handler / mask / pending)\n");
        return 0;
    }
    test(argv[1]);

    return 0;
}