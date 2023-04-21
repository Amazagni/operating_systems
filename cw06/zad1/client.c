#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include "converter.h"

#define MAX_COMMAND_LENGTH 256


key_t server_key, client_key;
int server_queue_id, client_queue_id, client_id;

void send_LIST() {
    struct msg_buff* msg_buff = malloc(MSG_BUFF_SIZE);
    msg_buff->client_id = client_id;
    msg_buff->type = 2;
    msgsnd(server_queue_id, msg_buff, MSG_BUFF_SIZE, 0);
}

void send_2ALL(char* message) {
    struct msg_buff* msg_buff = malloc(MSG_BUFF_SIZE);
    msg_buff->client_id = client_id;
    msg_buff->type = 3;
    strcpy(msg_buff->message, message);

    msgsnd(server_queue_id, msg_buff, MSG_BUFF_SIZE, 0);
}

void send_2ONE(int send_to_id, char* message) {
    struct msg_buff* msg_buff = malloc(MSG_BUFF_SIZE);
    msg_buff->client_id = client_id;
    msg_buff->type = 4;
    msg_buff->send_to_client_id = send_to_id;
    strcpy(msg_buff->message, message);
    printf("%s \n", msg_buff->message);
    msgsnd(server_queue_id, msg_buff, MSG_BUFF_SIZE, 0);
}

void send_STOP() {
    struct msg_buff* msg_buff = malloc(MSG_BUFF_SIZE);
    msg_buff->client_id = client_id;
    msg_buff->type = 5;
    msgsnd(server_queue_id, msg_buff, MSG_BUFF_SIZE, 0);
    msgctl(client_queue_id, IPC_RMID, NULL);
    printf("Client %d closing...\n", client_id);
    exit(0);
}

void handle_server_message() {
    struct msg_buff* msg_buff = malloc(MSG_BUFF_SIZE);
    while (msgrcv(client_queue_id, msg_buff, MSG_BUFF_SIZE, 0, 0) >= 0) {
        if (msg_buff->type == 5) {
            kill(0, SIGINT);
        }
        else {
        printf("Received a message: %s \n", msg_buff->message);
        printf("Message was sent at: %s \n\n", msg_buff->date);
        }
    }
}



int main() {

    srand((time(NULL)));
    server_key = ftok(HOME_PATH, SERVER_ID);
    server_queue_id = msgget(server_key, 0);
    client_key = ftok(HOME_PATH, rand() % 500 + 2);
    client_queue_id = msgget(client_key, IPC_CREAT | 0666);
    struct msg_buff* msg_buff = malloc(MSG_BUFF_SIZE);
    msg_buff -> type = 1;
    msg_buff -> key = client_key;

    msgsnd(server_queue_id, msg_buff, MSG_BUFF_SIZE, 0);
    msgrcv(client_queue_id, msg_buff, MSG_BUFF_SIZE, 0, 0);

    client_id = msg_buff -> client_id;

    char line[MAX_COMMAND_LENGTH];
    char* word;
    char delim[] = " \n\t";
    signal(SIGINT, send_STOP);

    if (fork() == 0) {
        while (1) {
            handle_server_message();
        }
    }

    while (1) {
        fgets(line, MAX_COMMAND_LENGTH, stdin);
        word = strtok(line, delim);
        if (word == NULL) continue;
        char* option = "LIST";
        if (strcmp(option, word) == 0) {
            send_LIST();
            continue;
        }
        option = "2ALL";
        if (strcmp(option, word) == 0) {
            word = strtok(NULL, delim);
            if (word != NULL) {
                send_2ALL(word);
            }
            continue;
        }
        option = "2ONE";
        if (strcmp(option, word) == 0) {
            word = strtok(NULL, delim);
            if (word != NULL) {
                int send_to_id = atoi(word);
                word = strtok(NULL, delim);
                if (word != NULL) {
                    send_2ONE(send_to_id, word);
                }
            }
            continue;
        }
        option = "STOP";
        if (strcmp(option, word) == 0){
            kill(0, SIGINT);
        }
        printf("Command not found\n");


    }


}