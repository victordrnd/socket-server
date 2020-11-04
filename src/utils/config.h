typedef struct{
    char *name;
    char **clients_name;
} Room;

typedef struct
{
    int *nb_room;
    Room *rooms;
} GameConfiguration;

typedef struct
{
    char *bind_ip;
    int *bind_port;
    int *max_simultaneous_connection;
    GameConfiguration *game_config;
} Config;


void *read_config(Config *configuration, char *filename);