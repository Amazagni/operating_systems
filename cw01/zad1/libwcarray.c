#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "libwcarray.h"

struct arrayInfo initializeArray(int maxNumOfCells){
    struct arrayInfo arrayInfo;
    arrayInfo.array = calloc(maxNumOfCells,sizeof(char*));
    arrayInfo.maxNumOfCells= maxNumOfCells;
    arrayInfo.currNumOfCells = 0;
    printf("Initialized array with %d cells \n", maxNumOfCells);
    return arrayInfo;
}

void loadToArray(struct arrayInfo* arrayInfo, char* sourceFile){
    FILE* file = fopen(sourceFile, "r");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    char* data = calloc(size, sizeof(char)); //size is a number of Baits, sizeof(char) equals to one Bait
    fseek(file, 0, SEEK_SET);
    fread(data, 1, size, file);
    //finding first empty cell and updating it
    for(int i = 0; i < arrayInfo->maxNumOfCells; i++){
        if(arrayInfo->array[i] == NULL){//first empty cell
            arrayInfo->array[i] = data;
            break;
        }
    }
    arrayInfo->currNumOfCells += 1;
    fclose(file);
}

void countFromFile(struct arrayInfo* arrayInfo, char* fileName){//struct arrayInfo arrayInfo, char* fileName){
    char* prefix  = "wc ";
    char* postfix = " >> /tmp/tmp";
    char* sourceFile = "/tmp/tmp";
    char* command = (char*)malloc(1 + strlen(prefix) + strlen(fileName)+ strlen(postfix));
    strcpy(command,prefix);
    strcat(command,fileName);
    strcat(command, postfix);
    int worked = system(command);
    free(command);
    if(worked == -1){
        printf("Error, file not found\n");
        return;
    };
    // adding data to our array
    if(arrayInfo->currNumOfCells == arrayInfo->maxNumOfCells){
        printf("Array is already full\n");
    }
    else{
        loadToArray(arrayInfo, sourceFile);
        printf("Info has been loaded to array\n");
    }
    // deleting tmpFile
    prefix = "rm ";
    command = (char*)malloc(1+strlen(prefix) + strlen(sourceFile));
    strcpy(command,prefix);
    strcat(command,sourceFile);
    system(command);
    free(command);
}

char* getCellById(struct arrayInfo* arrayInfo, int index){
    if(index >= arrayInfo->maxNumOfCells){
        printf("Index out of range\n");
        return NULL;
    }
    return arrayInfo->array[index];
}

void deleteCellById(struct arrayInfo* arrayInfo, int index){
    if(index >= arrayInfo->maxNumOfCells){
        printf("Index out of range\n");
        return;
    }
    if(arrayInfo->array[index] == NULL){
        printf("Cell is already empty\n");
        return;
    }
    free(arrayInfo->array[index]);
    arrayInfo->array[index] = NULL;
   // printf("%s",arrayInfo->array[index]);
    arrayInfo->currNumOfCells -= 1;
    printf("Cell has been deleted\n");
}

void freeArray(struct arrayInfo* arrayInfo){
    for(int i = 0; i < arrayInfo->maxNumOfCells; i++){
        free(arrayInfo->array[i]);
    }
    free(arrayInfo->array);
    printf("Array has been deleted\n");
}

//int main(){
//    int a = 3;
//    struct arrayInfo arrayInfo = initializeArray(a);
//    printf("%d\n",arrayInfo.currNumOfCells);
//    char* text = "main.c";
//    countFromFile(&arrayInfo, text);
//    text = "memoryblockarray.c";
//    countFromFile(&arrayInfo, text);
//    countFromFile(&arrayInfo, text);
//    printf("%d\n",arrayInfo.currNumOfCells);
//    printf("%s\n", getCellById(&arrayInfo, 1));
//    deleteCellById(&arrayInfo,1);
//    char* tmp = getCellById(&arrayInfo, 1);
//    if(tmp == NULL){
//        printf("NULL\n");
//    }
//    else{
//        printf("%s",tmp);
//    }
//    printf("%d\n",arrayInfo.currNumOfCells);
//    countFromFile(&arrayInfo, text);
//    tmp = getCellById(&arrayInfo, 1);
//    if(tmp == NULL){
//        printf("NULL\n");
//    }
//    else{
//        printf("%s",tmp);
//    }
//    printf("%d\n",arrayInfo.currNumOfCells);
//    freeArray(&arrayInfo);
//    return 0;
//}
