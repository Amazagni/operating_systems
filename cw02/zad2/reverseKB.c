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

    char* buff = (char*)malloc(1024 * sizeof(char));

    fseek(fFrom, 0, SEEK_END);
    int size = ftell(fFrom);
    int relSize, tmp;

    int i = size;
    while (i > 0){
        tmp = i;
        i -= 1024;
        if(i < 0)i = 0;
        fseek(fFrom,i,SEEK_SET);
        fread(buff,1,1024,fFrom);
        relSize = tmp;
        if(tmp > 1024)relSize = 1024;
        char* rev =(char*)malloc(relSize * sizeof(char));
        for(int j = 0; j < relSize; j++){
            rev[relSize - 1 - j] = buff[j];
        }
        fwrite(rev,1,relSize,fTo);
        free(rev);
    }

    fclose(fFrom);
    fclose(fTo);
    free(buff);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Real time using 1024 Bajts: %lu ns \n", end.tv_nsec - start.tv_nsec);

    return 0;

}
