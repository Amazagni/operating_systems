#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "values.h"
#include "queue.h"

char queue_pop(char *queue) {
    if(queue_empty(queue)) {
        printf("Error, queue is empty\n");
        return ' ';
    }
    char letter = queue[0];
    memcpy(queue, queue + 1, strlen(queue) + 1);
    return letter;
}

void queue_push(char *queue, char letter) {
    if (queue_full(queue)) {
        printf("Error, queue is full.\n");
        return;
    }
    int size = strlen(queue);
    queue[size] = letter;
}

bool queue_full(char *queue) {
    return (strlen(queue) + 1 == BUFFER_SIZE);
}

bool queue_empty(char *queue) {
    return (strlen(queue) == 0);
}