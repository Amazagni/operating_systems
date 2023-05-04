#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shared_mem.h"
#include "my_semaphore.h"
#include "values.h"
#include "queue.h"

int sem_queue;
int sem_chairs;
int sem_barbers;

void open_semaphores() {
    sem_queue = open_semaphore(SEMAPHORE_QUEUE);
    sem_chairs = open_semaphore(SEMAPHORE_CHAIRS);
    sem_barbers = open_semaphore(SEMAPHORE_BARBERS);
}

int main() {
    srand(time(NULL));
    char *queue = attach_shared_memory(HOME_PATH, BUFFER_SIZE);
    open_semaphores();
    if (queue_full(queue)) {
        printf("Queue is already full\n");
        return -1;
    }
    decrement(sem_queue);
    printf("New client came\n");
    queue_push(queue, '0');

    detach_shared_memory(queue);

    return 0;
}

