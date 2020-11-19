#ifndef CONFIG_RESULT_H
#define CONFIG_RESULT_H

#include "../../../common/game.h"

void open_csv(char *filename);

void write_header(const char *filename);
void write_line(const char *filename,Game *data,int client_id);

#endif
