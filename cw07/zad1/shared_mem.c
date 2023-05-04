#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include "shared_mem.h"

char *attach_shared_memory(const char* filename, int size) {
    key_t key = ftok(filename, 0);
    int shared_memory_id = shmget(key, size, 0666 | IPC_CREAT);
    char *shared_memory;
    shared_memory = shmat(shared_memory_id, NULL, 0);
    return shared_memory;
}

void detach_shared_memory(char *shared_memory) {
    shmdt(shared_memory);
}

void destroy_shared_memory(const char *filename) {
    key_t key = ftok(filename, 0);
    int shared_memory_id = shmget(key, 0, 0666 | IPC_CREAT);
    shmctl(shared_memory_id, IPC_RMID, NULL);
}