#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "communication.h"
#include "actions.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
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
    send_packet(CONNECT, NULL, (size_t)0);

    //Creation d'un pthread de lecture
    pthread_create(&threads.socket_thread, 0, listen_socket_thread_process, &cnx->sock);
    //write(connection->sock,"Main APP Still running",15);
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
    Connection *cnx = (Connection *)malloc(sizeof(Connection));

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
    while ((len = read(sockfd, buffer_in, BUFFERSIZE)) != 0)
    {
        unsigned char *buffer = (unsigned char *)malloc(sizeof(Encapsulation));
        memcpy(buffer, buffer_in, sizeof(Encapsulation));
        printf("Received buffer len : %d\n", len);
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
    write(cnx->sock, (const unsigned char *)&packet, sizeof(Encapsulation));
}
/**
 * @brief Close connection between client and server
 * 
 */
void close_connection()
{
    pthread_cancel(threads.stdin_thread);
    close(cnx->sock);
    // close_main_window(TRUE);
}
