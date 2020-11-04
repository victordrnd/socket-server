#include <stdlib.h>
#include <libconfig.h>
#include "config.h"

void parse_game_configuration(GameConfiguration *game_configuration, config_setting_t *setting)
{
    game_configuration->nb_room = config_setting_length(setting);
    game_configuration->rooms = malloc((int)game_configuration->nb_room * sizeof(Room));
    Room *wp = game_configuration->rooms;
    for (int i = 0; i < game_configuration->nb_room; ++i)
    {
        config_setting_t *current_room_config = config_setting_get_elem(setting, i);
        config_setting_lookup_string(current_room_config, "name", &wp->name);
        printf("%s\n", wp->name);
        config_setting_t *clients_room_config = config_setting_get_member(current_room_config, "clients");
        wp->clients_name = (char **)malloc((int)2 * sizeof(char *));
        for (int j = 0; j < 2; j++)
        {
            wp->clients_name[j] = (char *)malloc(100 * sizeof(char));
            config_setting_t *client_name_config = config_setting_get_elem(clients_room_config, j);
            config_setting_lookup_string(client_name_config, "name", &wp->clients_name[j]);
            printf("%s\n", wp->clients_name[j]);
        }
        game_configuration->rooms[i] = *wp;
        wp++;
    }
}

void *read_config(Config *configuration, char *filename)
{
    config_t cfg;
    config_setting_t *setting;
    config_init(&cfg);
    configuration = malloc(sizeof(Config));

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
        GameConfiguration *game_configuration = malloc(sizeof(GameConfiguration));
        parse_game_configuration(&game_configuration, setting);
        configuration->game_config = game_configuration;
#if DEBUG
        printf("bind ip : %s\n", configuration->bind_ip);
        printf("bind port : %d\n", configuration->bind_port);
#endif
    }
}