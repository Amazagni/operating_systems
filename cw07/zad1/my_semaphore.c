#include <sys/ipc.h>
#include <stdlib.h>
#include "my_semaphore.h"
#include "values.h"


int create_semaphore(const char *file, int initial) {
    key_t key = ftok(HOME_PATH, file[0]);
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    semctl(semid, 0, SETVAL, initial);
    return semid;
}

int open_semaphore(const char *file) {
    key_t key = ftok(HOME_PATH, file[0]);
    if (key == -1) {
        return -1;
    }
    return semget(key, 1, 0);
}

void unlink_semaphore(const char* file) {
    int semid = open_semaphore(file);
    semctl(semid, 0, IPC_RMID);
}

void decrement(int sem) {
    struct sembuf operation = { 0, -1, 0 };
    if (semop(sem, &operation, 1) == -1) {
        perror("aquire");
    }
}

void increment(int sem) {
    struct sembuf operation = { 0, 1, 0 };
    if (semop(sem, &operation, 1) == -1) {
        perror("release");
    }

}