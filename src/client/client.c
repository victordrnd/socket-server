/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include <stdio.h>
#include <argp.h>

#include "utils/config.h"
#include "interfaces/launch.h"
#include "game/game.h"
#include "network/communication.h"

Config *configuration;

typedef struct 
{
    char *args[2];
    int client_id, host_port; // Arguments for -c and -p
    char *host_ip; //Argument for -h
} Arguments;

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    Arguments *arguments = (Arguments *) state->input;

    switch (key)
    {
    case 'c':
        arguments->client_id = atoi(arg);
        configuration->client_id = arguments->client_id; 
        break;
    case 'h':
        arguments->host_ip = arg;
        configuration->ip = arguments->host_ip; 
        break;
    case 'p':
        arguments->host_port = atoi(arg);
        configuration->port = arguments->host_port;
        break;
    case ARGP_KEY_ARG:
        if (state->arg_num >= 3)
        {
            argp_usage(state);
        }
        arguments->args[state->arg_num] = arg;
        break;
    }
    return 0;
}


static struct argp_option options[] =
    {
        {"client_id", 'c', "1", 0, "Force client_id over config file"},
        {"host", 'h', "127.0.0.1", 0, "Force server_ip over config file"},
        {"port", 'p', "7799", 0, "Force server_port over config file"},
        {0}};


static char doc[] = "client -- Dilemme du prisonnier de l'Institut des Sciences Cognitives  \v";

static struct argp argp = {options, parse_opt, "", doc};


int main(int argc, char **argv)
{
    Arguments arguments;
    configuration = init_configuration();
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    char *executable_path = config_get_executable_path();
    read_config(strcat(executable_path, "/config/client_config.cfg"));
    init_game();
    init_main_window(argc, argv);
    init_communication(configuration);
    gtk_main();
    return (EXIT_SUCCESS);
}
