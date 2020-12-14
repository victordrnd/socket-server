/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#ifndef SRC_SERVER_NETWORK_COMMUNICATION_H_
#define SRC_SERVER_NETWORK_COMMUNICATION_H_
#include "../utils/config.h"
#include "../../common/protocol/protocol.h"
#include <netinet/in.h>
#include <sys/socket.h>
#define MAXSIMULTANEOUSCLIENTS 50

typedef struct
{
    int sockfd;
    struct sockaddr address;
    int addr_len;
    unsigned int client_id;
} connection_t;

void init_sockets_array(void);
void add(connection_t *connection);
void del(connection_t *connection);
void *threadProcess(void *ptr);
int create_server_socket(Config *configuration);

connection_t *get_connection(unsigned int client_id);
void send_packet(unsigned int client_id, enum verbs action, void *data, size_t data_size);


#endif //SRC_SERVER_NETWORK_COMMUNICATION_H_
