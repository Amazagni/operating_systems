#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void testIgnore(){
    raise(SIGUSR1);
    printf("Child: Ignore test passed\n");

}

void testMask(){
    raise(SIGUSR1);
    printf("Child: Mask test passed\n");
}

void testPending(){

    sigset_t childPending;
    sigpending(&childPending);
    if(sigismember(&childPending, SIGUSR1)){
        printf("Child: SIGUSR1 pending ...\n");
    }
    else{
        printf("Child: SIGUSR1 not pending\n");
    }

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