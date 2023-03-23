#ifndef LIBWCARRAY_H
#define LIBWCARRAY_H
struct arrayInfo{
    char ** array;
    int maxNumOfCells;
    int currNumOfCells;
};
struct arrayInfo initializeArray(int maxNumOfCells);
void loadToArray(struct arrayInfo* arrayInfo, char* sourceFile);
void countFromFile(struct arrayInfo* arrayInfo, char* fileName);
char* getCellById(struct arrayInfo* arrayInfo, int index);
void deleteCellById(struct arrayInfo* arrayInfo, int index);
void freeArray(struct arrayInfo* arrayInfo);
#endif //LIBWCARRAY_H
