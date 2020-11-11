#include <stdlib.h>
#include <libconfig.h>
#include <assert.h>
#include <string.h>

#include "config.h"
#include "../../common/tests/network/network.h"
#ifndef NDEBUG
#include <stdbool.h>
#endif


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
        config_lookup_string(&cfg, "name", &configuration->name);
        config_lookup_string(&cfg, "server_ip", &configuration->ip);
        config_lookup_int(&cfg, "server_port", (int *) &configuration->port);
    }

#ifndef NDEBUG

        assert(strlen(configuration->name) > 1);
        char *ip = (char *) malloc(12 * sizeof(char));
        strcpy(ip, configuration->ip);
        assert(is_ip_valid(ip) == true);
        free(ip);

        printf("client name : %s\n", configuration->name);
        printf("server ip : %s\n", configuration->ip);
        printf("server port : %d\n", configuration->port);
#endif
}