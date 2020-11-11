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
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "network/clientcxnmanager.h"
#include "utils/config.h"
#include "interfaces/launch.h"
#include "game/game.h"
// #include "network/communication.h"

void *listen_for_entry_thread_process(Connection *cnx)
{
    char msg[100];
    do
    {
        fgets(msg, 100, stdin);
        //printf("sending : %s\n", msg);
        cnx->status = write(cnx->sock, msg, strlen(msg));
        //memset(msg,'\0',100);
    } while (cnx->status != -1);
    return NULL;
}

/*
 * 
 */
int main(int argc, char **argv)
{
    Config configuration;
    read_config(&configuration,(char const *) "include/config/client_config.cfg");

    Game game;
    init_game(&game);
    //init_communication(&configuration);
    
    pthread_t thread;
    pthread_t reading_thread;
    char msg[100];

    Connection cnx;
    cnx.sock = open_connection(&configuration);
    cnx.status = 0;
    strcpy(msg, "Hello from Xeon");
    printf("sending : %s\n", msg);
    write(cnx.sock, msg, strlen(msg));

    //Creation d'un pthread de lecture
    pthread_create(&thread, 0, threadProcess, &cnx);
    //write(connection->sock,"Main APP Still running",15);
    pthread_detach(thread);

    pthread_create(&reading_thread, 0, listen_for_entry_thread_process, &cnx);
    pthread_detach(reading_thread);
    init_main_window(argc, argv);
    return (EXIT_SUCCESS);
}
