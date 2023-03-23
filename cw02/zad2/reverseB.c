#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(int argc,char *argv[]){
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    char* from = argv[1];
    char* to = argv[2];

    FILE * fFrom = fopen(from, "r");
    if(!fFrom){
        printf("File not found");
        return 0;
    }
    FILE * fTo = fopen(to, "w");

    char* buff = (char*)malloc(sizeof(char));
    fseek(fFrom, 0, SEEK_END);

    int size = ftell(fFrom);


    for(int i = size-1 ; i >= 0; i--){
        fseek(fFrom, i, SEEK_SET);
        fread(buff, 1, 1, fFrom);
        fwrite(buff, 1, 1, fTo);
    }

    fclose(fFrom);
    fclose(fTo);
    free(buff);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Real time using 1 Bajt: %lu ns \n", end.tv_nsec - start.tv_nsec);

    return 0;

}
