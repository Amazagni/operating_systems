#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

void searchDirectory(char* path, char* toFind){

    
    DIR * dir = opendir(path);
    if(dir == NULL){
        perror(path);
        return;
    }
    struct stat buff;
    struct dirent *file;
    while((file = readdir(dir)) != NULL){

        stat(file->d_name, &buff);
        if(strcmp(file->d_name,"..")==0 || strcmp(file->d_name,".")==0)continue;
        char* newPath = (char*)malloc(2 + strlen(path) + strlen(file->d_name));
        strcpy(newPath, path);
        strcat(newPath, "/");
        strcat(newPath, file->d_name);
        if(file->d_type == DT_DIR){
         if(fork()==0){
             searchDirectory(newPath, toFind);
             exit(0);
         }//     exit(0);
         else{
             wait(0);
         }
        }
        else{

            FILE * f = fopen(newPath,"r");
            int len = strlen(toFind);
            if(len > PATH_MAX)continue;
            if(f == NULL)continue;
            char* beg = (char*)malloc(len + 1);
            fread(beg, 1, len, f);
            if(strcmp(beg,toFind) == 0){
                printf("%s  PID: %d \n",newPath, getpid());
            }
        }
        free(newPath);
    }
    closedir(dir);


}


int main(int argc, char *argv[]) {

    char* path = argv[1];
    char* toFind = argv[2];
    if(toFind == NULL){
        printf("Missing argument\n");
        return 0;
    }
    searchDirectory(path, toFind);

    return 0;
}