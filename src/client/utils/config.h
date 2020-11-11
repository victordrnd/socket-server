#ifndef CONFIG_HEADER_FILE_H
#define CONFIG_HEADER_FILE_H
typedef struct
{
    const char *name;
    const char *ip;
    unsigned int port;
} Config;


void read_config(Config *configuration, char const *filename);
#endif