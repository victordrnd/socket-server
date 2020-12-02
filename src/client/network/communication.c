/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "communication.h"
#include "actions.h"

static app_threads_t threads;
Connection *cnx;

/**
 * @brief Starts listening thread process and establish server connection
 * 
 * @param configuration app configuration
 */
void init_communication(Config *configuration)
{
    cnx = open_connection(configuration);
    send_connect_packet();

    pthread_create(&threads.socket_thread, 0, listen_socket_thread_process, &cnx->sock);
    pthread_detach(threads.socket_thread);
}

/**
 * @brief Open cpnnection socket with server
 * 
 * @param configuration client configuration
 * @return Connection* 
 */
Connection *open_connection(Config *configuration)
{
    cnx = (Connection *)malloc(sizeof(Connection));

    struct sockaddr_in serverAddr;
    int port = configuration->port;

    cnx->sock = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(configuration->ip);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    if (connect(cnx->sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0)
    {
        printf("Fail to connect to server");
        exit(-1);
    };
    return cnx;
}



/**
 * @brief Thread process for listening socket input
 * 
 * @param *ptr socket
 * @return void* 
 */
void *listen_socket_thread_process(void *ptr)
{
    char buffer_in[BUFFERSIZE];
    int sockfd = *((int *)ptr);
    int len;
    while ((len = read(sockfd, buffer_in, sizeof(Encapsulation))) != 0)
    {
        u_int8_t *buffer = (u_int8_t *) malloc(sizeof(Encapsulation));
        memcpy(buffer, buffer_in, sizeof(Encapsulation));
        Encapsulation *packet = (Encapsulation *)buffer;
        settle_action(packet);
    }
    close_connection();
    return NULL;
}


void send_packet(enum verbs action, void *data, size_t data_size)
{
    Encapsulation packet;
    encapsulate_data(&packet, config_get_client_id(), 0, action, data, data_size);
    write(cnx->sock, (const u_int8_t *)&packet, sizeof(Encapsulation));
}



/**
 * @brief Close connection between client and server
 * 
 */
void close_connection(void)
{
    pthread_cancel(threads.stdin_thread);
    close(cnx->sock);
}
