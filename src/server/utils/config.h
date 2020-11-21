#ifndef CONFIG_HEADER_FILE_H
#define CONFIG_HEADER_FILE_H

#include <stdbool.h>

typedef struct
{
    const char *name;
    unsigned int nb_rounds;
    unsigned int initial_amount;
    unsigned int *clients_id;
} Room;

typedef struct
{
    unsigned int nb_room;
    Room *rooms;
} GameConfiguration;

typedef struct
{
    const char *bind_ip;
    unsigned int bind_port;
    unsigned int max_simultaneous_connection;
    GameConfiguration *game_config;
    char executable_path[256];
} Config;

void read_config(Config *configuration, char *filename);
int get_opponent_id(unsigned int client_id);
bool is_client_exists(unsigned int client_id);
Room *get_client_room(unsigned int client_id);

unsigned int get_max_round_count(Room *room);
unsigned int get_initial_amount(Room *room);

char *get_executable_path();
char *init_executable_path(Config *configuration);

#endif //!CONFIG_HEADER_FILE_H