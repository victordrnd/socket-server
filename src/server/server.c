/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: aurelio
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <stdbool.h>
#include <assert.h>

#include "./network/srvcxnmanager.h"
#include "utils/config.h"

#include "utils/export/result.h"

/*
 *
 */

int main(int argc, char** argv) {
    Config *configuration = (Config *) malloc(sizeof(Config));
    read_config(configuration, "include/config/server_config.cfg");

    int sockfd = -1;
    int index = 1;
    connection_t *connection;
    pthread_t thread;    

    const char filename[] = "output/test";
    
    Game data;
    open_csv(filename);
    write_header(filename);
    write_line(filename,&data);
    write_line(filename,&data);
    

    /* init array*/
    init_sockets_array();
    /* create socket */
    sockfd = create_server_socket(configuration);

    /* listen on port , stack size 50 for incoming connections*/
    if (listen(sockfd, 50) < 0) {
        fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
        return -5;
    }

    printf("ready and listening\n");

    //Wait for connection
    while (true) {
        /* accept incoming connections */
        connection = (connection_t *) malloc(sizeof (connection_t));
        connection->sockfd = accept(sockfd, &connection->address,(unsigned int *) &connection->addr_len);
        connection->index = index++;
        if (connection->sockfd <= 0) {
            free(connection);
        } else {
            /* start a new thread but do not wait for it */
            pthread_create(&thread, 0, threadProcess, (void *) connection);
            pthread_detach(thread);
        }
    }
    return (EXIT_SUCCESS);
}

