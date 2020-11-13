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
    read_config(&configuration,(char const *) "include/config/client_config.cfg");
    
    Game game;
    init_game(&game);
    
    init_communication(&configuration);
    
    init_main_window(argc, argv);
    return (EXIT_SUCCESS);
}
