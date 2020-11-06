#include <stdlib.h>
#include <libconfig.h>
#include <assert.h>
#include <string.h>

#include "config.h"
#ifndef NDEBUG
#include <stdbool.h>
#include "../../common/tests/network/network.h"
#endif

/**
 * @brief Parse only game_configuration section of config file
 * 
 * @param game_configuration empty GameConfiguration struct to fill
 * @param setting game_configuration settings
 */
void parse_game_configuration(GameConfiguration *game_configuration, config_setting_t *settings)
{
    game_configuration = malloc(sizeof(GameConfiguration));
    game_configuration->nb_room = config_setting_length(settings);
    assert(game_configuration->nb_room == 2);
    game_configuration->rooms = malloc((int)game_configuration->nb_room * sizeof(Room));
    Room *wp = game_configuration->rooms;
    for (int i = 0; i < game_configuration->nb_room; ++i)
    {
        config_setting_t *current_room_config = config_setting_get_elem(settings, i);
        config_setting_lookup_string(current_room_config, "name", &wp->name);
        config_setting_lookup_int(current_room_config, "initial_amount", &wp->initial_amount);
        config_setting_lookup_int(current_room_config, "nb_games", &wp->nb_games);

        assert(strlen(wp->name) > 1);
        assert(wp->initial_amount == 50);
        assert(wp->nb_games == 10);

        config_setting_t *clients_room_config = config_setting_get_member(current_room_config, "clients");
        wp->clients_name = (char **)malloc((int)2 * sizeof(char *));
        for (int j = 0; j < 2; j++)
        {
            wp->clients_name[j] = (char *)malloc(100 * sizeof(char));
            config_setting_t *client_name_config = config_setting_get_elem(clients_room_config, j);
            config_setting_lookup_string(client_name_config, "name", &wp->clients_name[j]);
            assert(strlen(wp->clients_name[j]) > 1);
        }
        assert(sizeof(*wp) == sizeof(Room));
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
        config_lookup_string(&cfg, "bind_ip", &configuration->bind_ip);
        config_lookup_int(&cfg, "bind_port", &configuration->bind_port);
        config_lookup_int(&cfg, "max_simultaneous_connection", &configuration->max_simultaneous_connection);

        setting = config_lookup(&cfg, "game_configuration");
        GameConfiguration *game_configuration;
        parse_game_configuration(game_configuration, setting);
        configuration->game_config = game_configuration;
    }
#ifndef NDEBUG
    assert(configuration->bind_port > 1024);
    assert(configuration->max_simultaneous_connection == 50);
    assert(is_ip_valid(configuration->bind_ip) == true);
    printf("server ip : %s\n", configuration->bind_ip);
    printf("server port : %d\n", configuration->bind_port);
    printf("max simultaneous connection : %d\n", configuration->max_simultaneous_connection);
    assert(sizeof(*(configuration->game_config)) == sizeof(GameConfiguration));
#endif
}
