/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>
#include <netinet/tcp.h>

#include "communication.h"
#include "actions.h"
#include "../../common/tests/logs/logs.h"

connection_t *connections[MAXSIMULTANEOUSCLIENTS];

/**
 * @brief Init empty sockets array
 * 
 */
void init_sockets_array(void)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        connections[i] = NULL;
    }
}



/**
 * @brief Add connection to connections list
 * 
 * @param connection 
 */
void add(connection_t *connection)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        if (connections[i] == NULL)
        {
            connections[i] = connection;
            return;
        }
    }
    perror("Too much simultaneous connections");
    exit(-5);
}



/**
 * @brief Delete connection from connections list
 * 
 * @param connection 
 */
void del(connection_t *connection)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        if (connections[i] == connection)
        {
            connections[i] = NULL;
            return;
        }
    }
    perror("Connection not in pool ");
    exit(-5);
}



/**
 * Thread allowing server to handle multiple client connections
 * @param ptr connection_t 
 * @return 
 */
void *threadProcess(void *ptr)
{
    char buffer_in[BUFFERSIZE];

    int len;
    connection_t *connection;

    if (!ptr)
        pthread_exit(0);
    connection = (connection_t *)ptr;

    add(connection);

    while ((len = read(connection->sockfd, buffer_in, BUFFERSIZE)) > 0){

        int size = sizeof(Encapsulation);
        u_int8_t *buffer = (u_int8_t *)malloc(size);
        memcpy(buffer, buffer_in, size);
        Encapsulation *packet = (Encapsulation *)buffer;
        if (packet->action == CONNECT)
        {
            connection->client_id = packet->sender_id;
        }

        assert(sizeof(*packet) == sizeof(Encapsulation));
        settle_action(packet);

        memset(buffer_in, '\0', BUFFERSIZE);
    }
    debug_print("\033[1;32m#%d\033[0m Connection to client ended\n", connection->client_id);
    close(connection->sockfd);
    del(connection);
    free(connection);
    pthread_exit(0);
}



/**
 * @brief Create a server socket object
 * 
 * @param configuration 
 * @return int 
 */
int create_server_socket(Config *configuration)
{
    int sockfd = -1;
    struct sockaddr_in address;
    int port = configuration->bind_port;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd <= 0)
    {
        fprintf(stderr, "error: cannot create socket\n");
        return -3;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(configuration->bind_ip);
    address.sin_port = htons(port);

    /* prevent the 60 secs timeout */
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse));
    int flags = 1;
    setsockopt(sockfd, SOL_SOCKET, TCP_NODELAY, (void *)&flags, sizeof(flags));
    /* bind */
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
    {
        fprintf(stderr, "error: cannot bind socket to port %d\n", port);
        return -4;
    }

    return sockfd;
}



/**
 * @brief Get the connection object
 * 
 * @param client_id 
 * @return connection_t* 
 */
connection_t *get_connection(unsigned int client_id)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        if (connections[i] != NULL)
        {
            if (connections[i]->client_id == client_id)
                return connections[i];
        }
    }
    return NULL;
}



/**
 * @brief Send packet to client
 * 
 * @param client_id 
 * @param action 
 * @param data 
 * @param data_size 
 */
void send_packet(unsigned int client_id, enum verbs action, void *data, size_t data_size)
{
    Encapsulation packet;
    encapsulate_data(&packet, 0, client_id, action, data, data_size);
    connection_t *connection = get_connection(client_id);
    write(connection->sockfd, (const u_int8_t *)&packet, sizeof(Encapsulation));
}
