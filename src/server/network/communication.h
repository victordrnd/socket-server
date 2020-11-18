/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   srvcxnmanager.h
 * Author: aurelio
 *
 */
#include "../utils/config.h"
#include "../../common/protocol/protocol.h"
#ifndef SRVCXNMANAGER_H
#define SRVCXNMANAGER_H
#include <netinet/in.h>
#include <sys/socket.h>
#define BUFFERSIZE 2048
#define MAXSIMULTANEOUSCLIENTS 100

typedef struct
{
    int sockfd;
    struct sockaddr address;
    int addr_len;
    int index;
    unsigned int client_id;
} connection_t;

void init_sockets_array();
void add(connection_t *connection);
void del(connection_t *connection);
void *threadProcess(void *ptr);
int create_server_socket(Config *configuration);

connection_t *get_connection(unsigned int client_id);
void send_packet(unsigned int client_id, enum verbs action, void *data, size_t data_size);
connection_t *get_connections();


#endif /* SRVCXNMANAGER_H */
