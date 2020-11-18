#ifndef CONFIG_HEADER_FILE_H
#define CONFIG_HEADER_FILE_H


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
} Config;

void read_config(Config *configuration, char *filename);
int get_opponent_id(unsigned int client_id);


#endif //!CONFIG_HEADER_FILE_H