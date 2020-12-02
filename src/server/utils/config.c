/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include <stdlib.h>
#include <libconfig.h>
#include <assert.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>

#include "config.h"
#ifndef NDEBUG
#include "../../common/tests/network/network.h"
#include "../../common/tests/logs/logs.h"
#endif

Config *conf = NULL;


/**
 * @brief Init configuration
 * 
 * @return Config* 
 */
Config *init_configuration(void){
    conf = (Config *) malloc(sizeof(Config));
    init_executable_path();
    return conf;
}
/**
 * @brief Parse only game_configuration section of config file
 * 
 * @param game_configuration empty GameConfiguration struct to fill
 * @param setting game_configuration settings
 */
void parse_game_configuration(GameConfiguration *game_configuration, config_setting_t *settings)
{
    game_configuration->nb_room = config_setting_length(settings);
    assert(game_configuration->nb_room > 0);
    game_configuration->rooms = (Room *)malloc((int)game_configuration->nb_room * sizeof(Room));
    Room *wp = game_configuration->rooms;
    assert(sizeof(*wp) == sizeof(Room));
    for (int i = 0; i < (int)game_configuration->nb_room; ++i)
    {
        config_setting_t *current_room_config = config_setting_get_elem(settings, i);
        config_setting_lookup_string(current_room_config, "name", (const char **)&wp->name);
        config_setting_lookup_int(current_room_config, "initial_amount", (int *)&wp->initial_amount);
        config_setting_lookup_int(current_room_config, "nb_rounds", (int *)&wp->nb_rounds);
        config_setting_lookup_int(current_room_config, "waiting_time", (int *) &wp->waiting_time);
        assert(strlen(wp->name) > 1);
        assert(wp->initial_amount > 10);
        assert(wp->nb_rounds > 0);

        const config_setting_t *clients_room_config = config_setting_get_member(current_room_config, "clients");
        const int nb_players = config_setting_length(clients_room_config);
        wp->clients_id = (unsigned int *)malloc(nb_players * sizeof(int));
        for (int j = 0; j < nb_players; j++)
        {
            const config_setting_t *client_name_config = config_setting_get_elem(clients_room_config, j);
            config_setting_lookup_int(client_name_config, "client_id", (int *)&wp->clients_id[j]);
            assert(wp->clients_id[j] > 0);
        }
        game_configuration->rooms[i] = *wp;
        wp++;
    }
}

/**
 * @brief Read configuration file
 * 
 * @param configuration configuration struct to fill  
 * @param filename filename of the cfg file.
 */
void read_config(char *filename)
{
    assert(conf);
    config_t cfg;
    config_setting_t *setting;
    config_init(&cfg);

    if (!config_read_file(&cfg, filename))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
    }
    else
    {
        assert(sizeof(cfg) == sizeof(config_t));
        config_lookup_string(&cfg, "bind_ip", &conf->bind_ip);
        config_lookup_int(&cfg, "bind_port", (int *)&conf->bind_port);
        config_lookup_int(&cfg, "max_simultaneous_connection", (int *)&conf->max_simultaneous_connection);

        setting = config_lookup(&cfg, "game_configuration");
        GameConfiguration *game_configuration = (GameConfiguration *)malloc(sizeof(GameConfiguration));
        parse_game_configuration(game_configuration, setting);
        conf->game_config = game_configuration;
    }

#ifndef NDEBUG
    assert(conf->bind_port > 1024);
    assert(conf->max_simultaneous_connection == 50);
    assert(sizeof(*(conf->game_config)) == sizeof(GameConfiguration));
    char *ip = (char *)malloc(12 * sizeof(char));
    strcpy(ip, conf->bind_ip);
    assert(is_ip_valid(ip) == true);
    free(ip);
    debug_print_server_config(conf->bind_ip, conf->bind_port, conf->max_simultaneous_connection);
#endif
}

/**
 * @brief Check if client_id exists in config
 * 
 * @param client_id 
 * @return true 
 * @return false 
 */
bool is_client_exists(unsigned int client_id)
{

    GameConfiguration *game_config = conf->game_config;

    for (unsigned int i = 0; i < game_config->nb_room; i++)
    {
        Room current_room = game_config->rooms[i];
        unsigned int *wp = current_room.clients_id;
        while (wp != NULL)
        {
            if (*wp == client_id)
            {
                return true;
            }
            wp++;
        }
    }
    return false;
}

/**
 * @brief Get the client room object
 * 
 * @param client_id 
 * @return Room* 
 */
Room *get_client_room(unsigned int client_id)
{

    GameConfiguration *game_config = conf->game_config;

    for (unsigned int i = 0; i < game_config->nb_room; i++)
    {
        Room *current_room = &game_config->rooms[i];

        for (int j = 0; j < 2; j++)
        {
            if (current_room->clients_id[j] == client_id)
                return current_room;
        }
    }
    return NULL;
}

/**
 * @brief Get the opponent id object
 * 
 * @param client_id 
 * @return int 
 */
int get_opponent_id(unsigned int client_id) //recuperer l'id de l'adversaire
{
    Room *current_room = get_client_room(client_id);
    unsigned int *wp = current_room->clients_id;
    while (wp != NULL)
    {
        if (*wp != client_id)
        {
            return *wp;
        }
        wp++;
    }
    return -1;
}

/**
 * @brief Get the max round count object
 * 
 * @param room 
 * @return unsigned int 
 */
unsigned int get_max_round_count(Room *room)
{
    return room->nb_rounds;
}

/**
 * @brief Get the initial amount object
 * 
 * @param room 
 * @return unsigned int 
 */
unsigned int get_initial_amount(Room *room)
{
    return room->initial_amount;
}

/**
 * @brief Get the executable path object
 * 
 * @return char* 
 */
char *config_get_executable_path(void)
{
    char *executable_path = (char *)malloc(sizeof(conf->executable_path));
    memcpy(executable_path, conf->executable_path, sizeof(conf->executable_path));
    return executable_path;
}

/**
 * @brief Init executable path in config
 * 
 * @param configuration 
 * @return char* 
 */
char *init_executable_path(void)
{
    char filename[sizeof(conf->executable_path)];
    int count = readlink("/proc/self/exe", filename, sizeof(filename));
    if (count != -1)
    {
        memcpy(conf->executable_path, dirname(filename), sizeof(filename));
    }
    return conf->executable_path;
}