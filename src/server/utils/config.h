#ifndef CONFIG_HEADER_FILE_H
#define CONFIG_HEADER_FILE_H


typedef struct
{
    const char *name;
    int nb_games;
    int initial_amount;
    int *clients_id;
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
} Config;

void read_config(Config *configuration, char *filename);


#endif //!CONFIG_HEADER_FILE_H