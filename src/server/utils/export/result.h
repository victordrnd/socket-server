#ifndef CONFIG_RESULT_H
#define CONFIG_RESULT_H

#include "../../../common/game.h"

void open_csv(char *filename);

void write_header(char *filename);
void write_line(char *filename,Game);

#endif
