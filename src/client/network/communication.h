#ifndef COMMUNICATION_HEADER_H
#define COMMUNICATION_HEADER_H
#include "../utils/config.h"
#include <pthread.h>
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
void close_connection();
#endif