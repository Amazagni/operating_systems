//
// Created by osboxes on 4/27/23.
//

#ifndef CHUDYMARCIN_QUEUE_H
#define CHUDYMARCIN_QUEUE_H

#include <stdbool.h>

char queue_pop(char *queue);
void queue_push(char *queue, char letter);
bool queue_full(char *queue);
bool queue_empty(char *queue);
#endif //CHUDYMARCIN_QUEUE_H
