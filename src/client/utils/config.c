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
#include <stdbool.h>

#include "config.h"
#ifndef NDEBUG
#include "../../common/tests/logs/logs.h"
#include "../../common/tests/network/network.h"
#endif

Config *config = NULL;

/**
 * @brief Read configuration file
 * 
 * @param configuration current configuration (or empty)
 * @param filename filename of configuration file
 */
void read_config(Config *configuration, const char *filename)
{
    config_t cfg;
    config_init(&cfg);
    if (!config_read_file(&cfg, filename))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
    }
    else
    {
        if (!configuration->client_id){
            config_lookup_int(&cfg, "client_id", (int *)&configuration->client_id);
        }
        if (configuration->ip == NULL){
            config_lookup_string(&cfg, "server_ip", &configuration->ip);
        }
        if (!configuration->port){
            config_lookup_int(&cfg, "server_port", (int *)&configuration->port);
        }
        config = configuration;
    }

#ifndef NDEBUG
    assert(configuration->client_id > 0);
    char *ip = (char *)malloc(12 * sizeof(char));
    strcpy(ip, configuration->ip);
    assert(is_ip_valid(ip) == true);
    free(ip);

    debug_print_client_config(configuration->client_id, configuration->ip, configuration->port);
#endif
}

unsigned int config_get_client_id(void)
{
    return config->client_id;
}

const char *config_get_server_ip(void)
{
    return config->ip;
}

unsigned int config_get_server_port(void)
{
    return config->port;
}

char *get_executable_path(void)
{
    char *executable_path = (char *)malloc(sizeof(config->executable_path));
    memcpy(executable_path, config->executable_path, sizeof(config->executable_path));
    assert(strlen(executable_path) > 0);
    return executable_path;
}
char *init_executable_path(Config *configuration)
{
    config = configuration;
    char filename[sizeof(config->executable_path)];
    int count = readlink("/proc/self/exe", filename, sizeof(filename));
    if (count != -1)
    {
        memcpy(configuration->executable_path, dirname(filename), sizeof(filename));
    }
    return config->executable_path;
}