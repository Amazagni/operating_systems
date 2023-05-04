#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/msg.h>
#include <assert.h>
#include <stdbool.h>
#include <semaphore.h>
#include "shared_mem.h"
#include "my_semaphore.h"
#include "values.h"

#define HAIRCUT_BASE_TIME 500000

int sem_queue;
int sem_chairs;
int sem_barbers;

void open_semaphores() {
    sem_queue = open_semaphore(SEMAPHORE_QUEUE);
    sem_chairs = open_semaphore(SEMAPHORE_CHAIRS);
    sem_barbers = open_semaphore(SEMAPHORE_BARBERS);
}

int main() {

    srand((time(NULL)));
    char *queue = attach_shared_memory(HOME_PATH, BUFFER_SIZE);
    open_semaphores();
    printf("New barber spawned %d\n", getpid());
    increment(sem_barbers);
    while (true) {
        decrement(sem_barbers);
        decrement(sem_chairs);
        increment(sem_queue);
        queue_pop(queue);
        printf("Barber starts doing the haircut %d\n",getpid());
        usleep((rand() % 10 + 1) * HAIRCUT_BASE_TIME);
        printf("Barber finished the haircut %d\n", getpid());
        increment(sem_chairs);
        increment(sem_barbers);
        if (queue_empty(queue)) {
            usleep(3000000);
            if (queue_empty(queue)) {
                break;
            }
        }
    }
    detach_shared_memory(queue);
    return 0;
}

