#ifndef CHUDYMARCIN_SEMAPHORE_H
#define CHUDYMARCIN_SEMAPHORE_H
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
int create_semaphore(const char *filename, int initial);
int open_semaphore(const char *filename);
void unlink_semaphore(const char* filename);
void increment(int sem);
void decrement(int sem);
#endif //CHUDYMARCIN_SEMAPHORE_H
