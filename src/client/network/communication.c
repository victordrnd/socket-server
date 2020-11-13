#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "communication.h"
#include "../interfaces/launch.h"
#include "../../common/protocol/protocol.h"
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

    char msg[100] = "Hello from client: ";

    cnx = open_connection(configuration);
    char text[50];
    sprintf(text, "%d", configuration->client_id);
    strcat(msg, text);
    // printf("sending : %s\n", msg);
    //write(cnx->sock, msg, strlen(msg));

    Test t;
    t.x = 5;
    t.y = 4;
    int size = sizeof(Encapsulation);
    Encapsulation packet;
    encapsulate_data(&packet, config_get_client_id(), 1, CONNECT, &t, sizeof(Test));

    unsigned char *buffer = (unsigned char *)malloc(size);
    memcpy(buffer, (const unsigned char *)&packet, size);
    write(cnx->sock, (const unsigned char *)&packet, size);
    for (int i = 0; i < size; i++)
        printf("%02X ", buffer[i]);
    printf("\n");
    //Creation d'un pthread de lecture
    pthread_create(&threads.socket_thread, 0, listen_socket_thread_process, &cnx->sock);
    //write(connection->sock,"Main APP Still running",15);
    pthread_detach(threads.socket_thread);

    pthread_create(&threads.stdin_thread, 0, listen_stdin_thread_process, cnx);
    pthread_detach(threads.stdin_thread);
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

    //Configure settings of the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(configuration->ip);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Connect the socket to the server using the address
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
        if (strncmp(buffer_in, "exit", 4) == 0)
        {
            break;
        }
        pthread_mutex_lock(&mutex);
        printf("receive %d chars\n", len);
        printf("%.*s\n", len, buffer_in);
        
        pthread_mutex_unlock(&mutex);
    }
    close_connection();
    return NULL;
}

void *listen_stdin_thread_process(void *ptr)
{
    Connection *cnx = (Connection *)ptr;
    int status = cnx->status;
    int sockfd = cnx->sock;
    char msg[2048];
    do
    {
        fgets(msg, 100, stdin);
        pthread_mutex_lock(&mutex);
        // printf("sending : %s\n", msg);
        pthread_mutex_unlock(&mutex);
        status = write(sockfd, msg, strlen(msg));
    } while (status != -1);
    return NULL;
}

/**
 * @brief Close connection between client and server
 * 
 */
void close_connection()
{
    pthread_cancel(threads.stdin_thread);
    close(cnx->sock);
    close_main_window(TRUE);
}
