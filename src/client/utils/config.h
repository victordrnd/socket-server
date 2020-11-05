#ifndef CONFIG_HEADER_FILE_H
#define CONFIG_HEADER_FILE_H
typedef struct
{
    char *name;
    char *ip;
    int *port;
} Config;


void read_config(Config *configuration, char *filename);
#endif