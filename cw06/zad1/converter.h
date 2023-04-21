#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/msg.h>


#ifndef CHUDYMARCIN_CONSTANTS_H
#define CHUDYMARCIN_CONSTANTS_H

#define SERVER_ID 1
#define MAX_NO_CLIENTS 15
#define MAX_MESSAGE_SIZE 512
#define HOME_PATH getenv("HOME")
#define MAX_DATE_SIZE 64


struct msg_buff {
    long type;
    key_t key;
    char message[MAX_MESSAGE_SIZE];
    char date[MAX_DATE_SIZE];
    int client_id;
    int send_to_client_id;
};

const int MSG_BUFF_SIZE = sizeof(struct msg_buff) - sizeof(long);


#endif //CHUDYMARCIN_CONSTANTS_H