/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#ifndef COMMUNICATION_HEADER_H
#define COMMUNICATION_HEADER_H
#include "../utils/config.h"
#include <pthread.h>
#include "../../common/protocol/protocol.h"
#define BUFFERSIZE 2048

typedef struct {
    pthread_t stdin_thread;
    pthread_t socket_thread;
} app_threads_t;


typedef struct {
    int sock;
    int status;
} Connection;

void init_communication(Config *configuration);
Connection *open_connection(Config *configuration);
void *listen_socket_thread_process(void *ptr);
void *listen_stdin_thread_process(void *ptr);
void send_packet(enum verbs action, void *data, size_t data_size);
void close_connection(void);
#endif