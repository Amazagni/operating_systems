#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../zad1/libwcarray.h"
#include <sys/times.h>
#include <unistd.h>
#include <time.h>

struct arrayInfo arrayInfo;

void init(char* numberOfCells){
    arrayInfo = initializeArray(atoi(numberOfCells));
}
void count(char* fileName){
    countFromFile(&arrayInfo, fileName);
}
void show(char* index){
    int i = atoi(index);
    char* result = getCellById(&arrayInfo, i);
    if(i >= arrayInfo.maxNumOfCells)return;
    if(result == NULL)printf("NULL\n");
    else {printf("%s",result);}
}
void delete(char* index){
    deleteCellById(&arrayInfo, atoi(index));
}
void destroy(){
    freeArray(&arrayInfo);
}
void printTimes(struct tms tmsEnd, struct tms tmsStart, struct timespec clockStart, struct timespec clockEnd, char* inf){
//    double realTime;
//    double userTime;
//    double systemTime;
//    long tics = sysconf(_SC_CLK_TCK);//numer of clock tics per second
//    realTime = (double)(clockEnd - clockStart)/(double)tics;
//    userTime = (double)(tmsEnd.tms_utime - tmsStart.tms_utime)/(double)tics;
//    systemTime = (double)(tmsEnd.tms_stime - tmsStart.tms_stime)/(double)tics;
    printf("%s time real: %lu ns, user: %lu t, system: %lu t\n",inf, clockEnd.tv_nsec - clockStart.tv_nsec,
           tmsEnd.tms_utime - tmsStart.tms_utime, tmsEnd.tms_stime - tmsStart.tms_stime);
}
int main() {
    struct timespec st,en, stSum, enSum;
    struct tms tmsStartSum, tmsEndSum;
    times(&tmsStartSum);
    clock_gettime(CLOCK_REALTIME, &stSum);
    int isEmpty = 1;
    char line[200];
    char* word;
    char delim[] = " \n\t";
    struct tms tmsStart, tmsEnd;
    //clock_t clockStart, clockEnd;
    while(fgets(line, 200, stdin)){
        word = strtok(line, delim);
        if(word == NULL)continue;
        char* option = "init";
        if(strcmp(option, word) == 0){
            isEmpty = 0;
            word = strtok(NULL, delim);
            if(word == NULL){
                printf("Command requires argument\n");
                continue;
            }
            times(&tmsStart);
            clock_gettime(CLOCK_REALTIME, &st);
            init(word);
            times(&tmsEnd);
            clock_gettime(CLOCK_REALTIME, &en);
            printTimes(tmsEnd, tmsStart, st, en, "Init");
            continue;
        }
        if(isEmpty == 1){
            printf("Initialize array first\n");
            continue;
        }

        option = "count";
        if(strcmp(option, word) == 0){
            isEmpty = 0;
            word = strtok(NULL, delim);
            if(word == NULL){
                printf("Command requires argument\n");
                continue;
            }
            clock_gettime(CLOCK_REALTIME, &st);
            times(&tmsStart);
            count(word);
            times(&tmsEnd);
            clock_gettime(CLOCK_REALTIME, &en);
            printTimes(tmsEnd, tmsStart, st, en, "Count");
            continue;
        }
        option = "show";
        if(strcmp(option, word) == 0){
            word = strtok(NULL, delim);
            if(word == NULL){
                printf("Command requires argument\n");
                continue;
            }
            times(&tmsStart);
            clock_gettime(CLOCK_REALTIME, &st);
            show(word);
            times(&tmsEnd);
            clock_gettime(CLOCK_REALTIME, &en);
            printTimes(tmsEnd, tmsStart, st, en, "Show");
            continue;
        }
        option = "delete";
        if(strcmp(option, word) == 0){
            word = strtok(NULL, delim);
            if(word == NULL){
                printf("Command requires argument\n");
                continue;
            }
            times(&tmsStart);
            clock_gettime(CLOCK_REALTIME, &st);
            delete(word);
            times(&tmsEnd);
            clock_gettime(CLOCK_REALTIME, &en);
            printTimes(tmsEnd, tmsStart, st, en, "Delete");
            continue;
        }
        option = "destroy";
        if(strcmp(option, word) == 0){
            clock_gettime(CLOCK_REALTIME, &st);
            times(&tmsStart);
            destroy();
            times(&tmsEnd);
            clock_gettime(CLOCK_REALTIME, &en);
            printTimes(tmsEnd, tmsStart, st, en, "Destroy");
            isEmpty = 1;
            continue;
        }
        printf("Command not found\n");
    }
    times(&tmsEndSum);
    clock_gettime(CLOCK_REALTIME, &enSum);
    printTimes(tmsEndSum, tmsStartSum, stSum, enSum, "TOTAL");

    return 0;
}
