#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(int argc,char *argv[]){
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    char toFind = argv[1][0];
    char replacement = argv[2][0];
    char* from = argv[3];
    char* to = argv[4];
    FILE * fFrom = fopen(from, "r");
    if(!fFrom){
        printf("File not found");
        return 0;
    }
    FILE * fTo = fopen(to, "w");
    char* buff = (char*)malloc(sizeof(char));

    while(fread(buff, 1, 1, fFrom) != 0){
        if(buff[0] == toFind){
            buff[0] = replacement;
        }

        fwrite(buff,1,1 ,fTo);
    }
    fclose(fFrom);
    fclose(fTo);
    free(buff);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Real time using lib: %lu ns \n", end.tv_nsec - start.tv_nsec);

    return 0;

}
