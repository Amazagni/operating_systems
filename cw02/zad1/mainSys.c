#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    char toFind = argv[1][0];
    char replacement = argv[2][0];
    char* from = argv[3];
    char* to = argv[4];
    int fdFrom = open(from, O_RDONLY);
    int fdTo = open(to,  O_WRONLY | O_APPEND | O_CREAT, 0666);
    char* buff = (char*)malloc(sizeof(char));

    while(read(fdFrom, buff, 1) != 0){
        if(buff[0] == toFind){
            buff[0] = replacement;
        }
        write(fdTo, buff, 1);
    }
    close(fdFrom);
    close(fdTo);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Real time using sys: %lu ns \n", end.tv_nsec - start.tv_nsec);

    return 0;

}