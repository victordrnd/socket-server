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

#include "config.h"
#ifndef NDEBUG
#include "../../common/tests/logs/logs.h"
#include "../../common/tests/network/network.h"
#endif

Config *config = NULL;

/**
 * @brief Init configuration
 * 
 * @return Config* 
 */
Config *init_configuration(void){
    config = (Config *) malloc(sizeof(Config));
    init_executable_path();
    return config;
}


/**
 * @brief Read configuration file
 * 
 * @param configuration current configuration (or empty)
 * @param filename filename of configuration file
 */
void read_config(const char *filename)
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
        if (!config->client_id){
            config_lookup_int(&cfg, "client_id", (int *)&config->client_id);
        }
        if (config->ip == NULL){
            config_lookup_string(&cfg, "server_ip", &config->ip);
        }
        if (!config->port){
            config_lookup_int(&cfg, "server_port", (int *)&config->port);
        }
    }

#ifndef NDEBUG
    assert(config->client_id > 0);
    char *ip = strdup(config->ip);
    assert(is_ip_valid(ip) == true);
    free(ip);
    debug_print_client_config(config->client_id, config->ip, config->port);
#endif
}



/**
 * @brief 
 * 
 * @return unsigned int 
 */
unsigned int config_get_client_id(void)
{
    return config->client_id;
}

/**
 * @brief Get server IP
 * 
 * @return const char* 
 */
const char *config_get_server_ip(void)
{
    return config->ip;
}


/**
 * @brief Get server port
 * 
 * @return unsigned int 
 */
unsigned int config_get_server_port(void)
{
    return config->port;
}


/**
 * @brief Get executable path
 * 
 * @return char* 
 */
char *config_get_executable_path(void)
{
    char *executable_path = strdup(config->executable_path);
    assert(strlen(executable_path) > 0);
    return executable_path;
}


/**
 * @brief Init executable path
 * 
 * @return char* 
 */
char *init_executable_path(void)
{
    char filename[sizeof(config->executable_path)];
    int count = readlink("/proc/self/exe", filename, sizeof(filename));
    if (count != -1)
    {
        memcpy(config->executable_path, dirname(filename), sizeof(filename));
    }
    return config->executable_path;
}