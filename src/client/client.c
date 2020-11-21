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
#include "utils/config.h"
#include "interfaces/launch.h"
#include "game/game.h"
#include "network/communication.h"
int main(int argc, char **argv)
{

    Config configuration;
    init_executable_path(&configuration);
    char *executable_path = get_executable_path();
    read_config(&configuration,strcat(executable_path, "/config/client_config.cfg"));
    free(executable_path);
    Game game;
    init_game(&game);

    init_main_window(argc, argv);
    init_communication(&configuration);
    gtk_main();
    return (EXIT_SUCCESS);
}
