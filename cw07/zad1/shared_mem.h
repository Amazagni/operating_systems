
#ifndef CHUDYMARCIN_SHARED_MEM_H

#define CHUDYMARCIN_SHARED_MEM_H
char *attach_shared_memory(const char* filename, int size);
void detach_shared_memory(char *shared_memory);
void destroy_shared_memory(const char *filename);
#endif //CHUDYMARCIN_SHARED_MEM_H
