#include <stdlib.h>
#include <libconfig.h>
#include <assert.h>
#include <string.h>

#include "config.h"
#ifndef NDEBUG
#include "../../common/tests/network/network.h"
#include "../../common/tests/logs/logs.h"
#endif


Config *conf = NULL;

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
        config_setting_lookup_int(current_room_config, "initial_amount",(int *) &wp->initial_amount);
        config_setting_lookup_int(current_room_config, "nb_rounds",(int *) &wp->nb_rounds);

        assert(strlen(wp->name) > 1);
        assert(wp->initial_amount > 10);
        assert(wp->nb_rounds > 0);

        const config_setting_t *clients_room_config = config_setting_get_member(current_room_config, "clients");
        const int nb_players = config_setting_length(clients_room_config);
        wp->clients_id = (unsigned int *)malloc(nb_players * sizeof(int));
        for (int j = 0; j < nb_players; j++)
        {
            // wp->clients_id[j] = malloc(sizeof(char));
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
void read_config(Config *configuration, char *filename)
{
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
        config_lookup_string(&cfg, "bind_ip", &configuration->bind_ip);
        config_lookup_int(&cfg, "bind_port", (int *)&configuration->bind_port);
        config_lookup_int(&cfg, "max_simultaneous_connection", (int *)&configuration->max_simultaneous_connection);

        setting = config_lookup(&cfg, "game_configuration");
        GameConfiguration *game_configuration = (GameConfiguration *)malloc(sizeof(GameConfiguration));
        
        parse_game_configuration(game_configuration, setting);
        configuration->game_config = game_configuration;

        conf = configuration;
    }

#ifndef NDEBUG
    assert(configuration->bind_port > 1024);
    assert(configuration->max_simultaneous_connection == 50);
    assert(sizeof(*(configuration->game_config)) == sizeof(GameConfiguration));
    char *ip = (char *)malloc(12 * sizeof(char));
    strcpy(ip, configuration->bind_ip);
    assert(is_ip_valid(ip) == true);
    free(ip);
    debug_print_server_config(configuration->bind_ip, configuration->bind_port, configuration->max_simultaneous_connection);
#endif
}

bool is_client_exists(unsigned int client_id) {

    GameConfiguration *game_config = conf->game_config;

    for(int i=0; i<game_config->nb_room; i++) //verifier si l'id du client est bien dans le fichier de configuration
    { 
        Room current_room = game_config->rooms[i];
        unsigned int *wp = current_room.clients_id; //wp = working pointer

        while(wp != NULL)
        {
            if(*wp == client_id)
            {
                return true;
            }
            wp++;
        }
    }
    return false;
}

Room* get_client_room(unsigned int client_id){

    GameConfiguration *game_config = conf->game_config;

    for(int i=0; i<game_config->nb_room; i++)
    {
        Room *current_room = &game_config->rooms[i];

        unsigned int *wp = current_room->clients_id; //wp = working pointer

        while(wp != NULL)
        {
            if(*wp == client_id)
            {
                return current_room;
            }
            wp++;
        }   
    }
    return NULL;
}

int get_opponent_id(unsigned int client_id) //recuperer l'id de l'adversaire
{ 
    Room *current_room = get_client_room(client_id);

    unsigned int *wp = current_room->clients_id;

    while (wp !=NULL)
    {
        if (*wp != client_id)
        {
            return *wp;
        }
        
        wp++;
    }
    return -1;
}

int get_max_round_count(Room *room){
    return room->nb_rounds;
}

int get_initial_amount(Room *room) {
    return room->initial_amount;
}
