#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void printPID(){
    printf("PID: %d, PPID: %d\n",getpid(),getppid());
    exit(0);
}

int main(int argc, char *argv[]) {
    if(argc != 2){
        printf("One argument required\n");
        return 0;
    }

    int n = atoi(argv[1]);
    for(int i = 0; i < n; i++){
        if(fork()==0){
            printPID();
        }
        wait(0);
    }
    printf("argv[1] = %s\n",argv[1]);
}