
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/msg.h>
#include <assert.h>
#include "converter.h"

#define LOG_FILE "server_logs.txt"

key_t clients_queues[MAX_NO_CLIENTS];
int server_queue;
FILE* f;

void log_msg(struct msg_buff* msg_buff) {
    char date[64];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    size_t ret = strftime(date, sizeof(date), "%c", tm);
    assert(ret);
    if (msg_buff->type == 1) {
        fprintf(f, "%s, New client added \n", date);
        return;
    }
    if (msg_buff->type == 2) {
        fprintf(f, "%s, ClientID: %d,  Listed all clients \n", date, msg_buff->client_id);
        return;
    }
    if (msg_buff->type == 3) {
        fprintf(f, "%s, ClientID: %d,  Sent a message to all \n", date, msg_buff->client_id);
        return;
    }
    if (msg_buff->type == 4) {
        fprintf(f, "%s, ClientID: %d,  Sent a message to %d \n", date, msg_buff->client_id, msg_buff->send_to_client_id);
        return;
    }
    if (msg_buff->type == 5) {
        fprintf(f, "%s, ClientID: %d,  Closed \n", date, msg_buff->client_id);
        return;
    }
}

void handle_INIT(struct msg_buff* msg_buff) {
    int new_client_id = -1;
    for (int i = 0; i < MAX_NO_CLIENTS; i++) {
        if (clients_queues[i] == -1) {
            new_client_id = i;
            break;
        }
    }
    if (new_client_id == -1) {
        printf("Clients table is already full \n");
        return;
    }

    clients_queues[new_client_id] = msg_buff->key;
    msg_buff->client_id = new_client_id;
    int new_client_queue_id = msgget(msg_buff->key, 0);
    msgsnd(new_client_queue_id, msg_buff, MSG_BUFF_SIZE, 0);
}

void handle_LIST() {
    printf("IN HANDLE LIST\n");
    for (int i = 0; i < MAX_NO_CLIENTS; i++) {
        if (clients_queues[i] != -1) {
            printf("Client's ID: %d, Client't key: %d\n", i, clients_queues[i]);
        }
    }
}

void handle_2ALL(struct msg_buff* msg_buff) {
    printf("IN HANDLE 2ALL\n");
    char date[64];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    size_t ret = strftime(date, sizeof(date), "%c", tm);
    assert(ret);
    memcpy(msg_buff->date, date, sizeof(date));
    for (int i = 0; i < MAX_NO_CLIENTS; i++) {
        if (clients_queues[i] != -1) {
            printf("Sent to %d\n", i);
            msgsnd(msgget(clients_queues[i], 0), msg_buff, MSG_BUFF_SIZE, 0);
        }
    }
}

void handle_2ONE(struct msg_buff* msg_buff) {
    printf("IN HANDLE 2ONE\n");
    int client_id = msg_buff->send_to_client_id;
    if (client_id < 0 || client_id >= MAX_NO_CLIENTS || clients_queues[client_id] == -1) {
        printf("Client is not available\n");
        return;
    }
    char date[64];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    size_t ret = strftime(date, sizeof(date), "%c", tm);
    assert(ret);
    memcpy(msg_buff->date, date, sizeof(date));
    msgsnd(msgget(clients_queues[client_id], 0), msg_buff, MSG_BUFF_SIZE, 0);
}

void handle_STOP(struct msg_buff* msg_buff) {
    clients_queues[msg_buff->client_id] = -1;
}

void handle_CLOSE_SERVER() {
    struct msg_buff* msg_buff = malloc(MSG_BUFF_SIZE);
    msg_buff->type = 5;
    for (int i = 0; i < MAX_NO_CLIENTS; i++) {
        if (clients_queues[i] != -1) {
            msg_buff->client_id = clients_queues[i];
            msgsnd(msgget(clients_queues[i], 0), msg_buff, MSG_BUFF_SIZE, 0);
            msgrcv(server_queue, msg_buff, MSG_BUFF_SIZE, 5, 0);
        }
    }
    msgctl(server_queue, IPC_RMID, NULL);

    fprintf(f, "Server closing... \n");
    fclose(f);
    exit(0);
}

int main() {
    f = fopen(LOG_FILE, "a");
    signal(SIGINT, handle_CLOSE_SERVER);

    for (int i = 0; i < MAX_NO_CLIENTS; i++) {
        clients_queues[i] = -1;
    }

    key_t main_key = ftok(HOME_PATH, SERVER_ID);
    server_queue = msgget(main_key, IPC_CREAT | 0666);

    struct msg_buff* msg_buff = malloc(MSG_BUFF_SIZE);

    while (1) {
        msgrcv(server_queue, msg_buff, MSG_BUFF_SIZE, -100, 0);
        printf("%lu", msg_buff -> type);
        switch (msg_buff->type) {
            case 1:
                log_msg(msg_buff);
                handle_INIT(msg_buff);
                break;
            case 2:
                log_msg(msg_buff);
                handle_LIST();
                break;
            case 3:
                log_msg(msg_buff);
                handle_2ALL(msg_buff);
                break;
            case 4:
                log_msg(msg_buff);
                handle_2ONE(msg_buff);
                break;
            case 5:
                log_msg(msg_buff);
                handle_STOP(msg_buff);
                break;
            default:
                printf("Message type not found\n");
        }

    }
}