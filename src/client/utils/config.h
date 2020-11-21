#ifndef CONFIG_HEADER_FILE_H
#define CONFIG_HEADER_FILE_H

typedef struct
{
    unsigned int client_id;
    const char *ip;
    unsigned int port;
    char executable_path[256];
} Config;

void read_config(Config *configuration, char const *filename);

unsigned int config_get_client_id();
const char *config_get_server_ip();
unsigned int config_get_server_port();
char *get_executable_path();
char *init_executable_path(Config *config);
#endif