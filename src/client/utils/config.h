/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

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

unsigned int config_get_client_id(void);
const char *config_get_server_ip(void);
unsigned int config_get_server_port(void);
char *get_executable_path(void);
char *init_executable_path(Config *config);
#endif