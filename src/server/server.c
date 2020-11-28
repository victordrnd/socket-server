/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#include "./network/communication.h"
#include "utils/config.h"


int main(int argc __attribute__((unused)), char** argv) {
    Config *configuration = init_configuration();
    char *executable_path = config_get_executable_path();
    read_config(strcat(executable_path, "/config/server_config.cfg"));


    int sockfd = -1;
    connection_t *connection;
    pthread_t thread;    

    init_sockets_array();
    sockfd = create_server_socket(configuration);

    if (listen(sockfd, 50) < 0) {
        fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
        return -5;
    }

    printf("Ready and listening...\n");

    while (true) {
        connection = (connection_t *) malloc(sizeof (connection_t));
        connection->sockfd = accept(sockfd, &connection->address, (unsigned int *) &connection->addr_len);
        if (connection->sockfd <= 0) {
            free(connection);
        } else {
            pthread_create(&thread, 0, threadProcess, (void *) connection);
            pthread_detach(thread);
        }
    }
    return (EXIT_SUCCESS);
}

