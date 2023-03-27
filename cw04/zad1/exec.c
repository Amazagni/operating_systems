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
    execl("execChild" ,"execChild","ignore", NULL);
}


void testMask(){
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, NULL);
    raise(SIGUSR1);
    printf("Parent: Mask test passed\n");
    execl("execChild" ,"execChild","mask", NULL);
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
    execl("execChild" ,"execChild","pending", NULL);

}


void test (char* arg){
    if(strcmp(arg, "ignore") == 0){
        testIgnore();
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
    printf("Incorrect argument: ignore / mask / pending\n");
    return;
}

int main(int argc, char* argv[]) {

    if(argc != 2){
        printf("One argument required (ignore / mask / pending)\n");
        return 0;
    }
    test(argv[1]);

    return 0;
}