#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "shared_mem.h"
#include "my_semaphore.h"
#include "values.h"

int sem_queue;
int sem_chairs;
int sem_barbers;
int buffer_mutex;

void create_semaphores() {
    sem_queue =  create_semaphore(SEMAPHORE_QUEUE, QUEUE_SIZE);
    sem_chairs =  create_semaphore(SEMAPHORE_CHAIRS, CHAIR_NUMBER);
    sem_barbers =  create_semaphore(SEMAPHORE_BARBERS, 0);
}

int main() {
    printf("Simulation starting\n");

    attach_shared_memory(HOME_PATH, BUFFER_SIZE);

    create_semaphores();

    for(int i = 0; i < BARBER_NUMBER; i++)
        if (fork() == 0)
            execl("./barber", "barber", NULL);
    printf("Spawned %d barbers\n", BARBER_NUMBER);

    for(int i = 0; i < CUSTOMERS_NUMBER; i++)
        if (fork() == 0)
            execl("./client", "client", NULL);
    printf("Spawned %d customers.\n", CUSTOMERS_NUMBER);

    while(wait(NULL) > 0);

    unlink_semaphore(SEMAPHORE_QUEUE);
    unlink_semaphore(SEMAPHORE_CHAIRS);
    unlink_semaphore(SEMAPHORE_BARBERS);
    destroy_shared_memory(HOME_PATH);

    printf("Simulation ending\n");
    return 0;
}




