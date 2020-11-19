
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>

#include "communication.h"
#include "actions.h"
#include "../../common/tests/logs/logs.h"

connection_t *connections[MAXSIMULTANEOUSCLIENTS];

void init_sockets_array()
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        connections[i] = NULL;
    }
}

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
/*
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&lock);
pthread_mutex_unlock(&lock);
 */

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

    while ((len = read(connection->sockfd, buffer_in, BUFFERSIZE)) > 0)
    {
        
        int size = sizeof(Encapsulation);
        unsigned char *buffer = (unsigned char *)malloc(size);
        memcpy(buffer, buffer_in, size);
        Encapsulation *packet = (Encapsulation *)buffer;
        if (packet->action == CONNECT)
        {
            connection->client_id = packet->sender_id;
        }
#ifndef NDEBUG
        // printf("DEBUG-----------------------------------------------------------\n");
        // // printf("len : %i\n", len);
        // printf("Buffer : ");
        // for (int i = 0; i < size; i++)
        //     printf("%02X ", buffer[i]);
        // printf("\n");
        // printf("Sender_id : %d\n", packet->sender_id);
        // printf("Destination_id : %d\n", packet->destination_id);
        // printf("Action : %d\n", packet->action);
        // printf("Packet size : %d\n", sizeof(Encapsulation));
        // printf("Timestamp : %lld\n", (long long)packet->timestamp);
        // printf("----------------------------------------------------------------\n");
#endif

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

int create_server_socket(Config *configuration)
{
    int sockfd = -1;
    struct sockaddr_in address;
    int port = configuration->bind_port;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd <= 0)
    {
        fprintf(stderr, "%s: error: cannot create socket\n");
        return -3;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(configuration->bind_ip);
    address.sin_port = htons(port);

    /* prevent the 60 secs timeout */
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse));

    /* bind */
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
    {
        fprintf(stderr, "error: cannot bind socket to port %d\n", port);
        return -4;
    }

    return sockfd;
}

connection_t *get_connection(unsigned int client_id)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        if (connections[i] != NULL)
        {
            if (connections[i]->client_id == client_id){
                printf("client_id : %d\n",client_id);
                return connections[i];
            }
        }
    }
    return NULL;
}

void send_packet(unsigned int client_id, enum verbs action, void *data, size_t data_size)
{
    Encapsulation packet;
    encapsulate_data(&packet, 0, client_id, action, data, data_size);

    connection_t *connection = get_connection(client_id);
    write(connection->sockfd, (const unsigned char *)&packet, sizeof(Encapsulation));
#ifndef NDEBUG
    unsigned char *buffer = (unsigned char *)malloc(sizeof(Encapsulation));
    memcpy(buffer, (const unsigned char *)&packet, sizeof(Encapsulation));
    // printf("Sending buffer : \n");
    // for (int i = 0; i < sizeof(Encapsulation); i++)
    //     printf("%02X ", buffer[i]);
    // printf("\n");
#endif
}
