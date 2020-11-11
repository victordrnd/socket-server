#ifndef CONFIG_RESULT_H
#define CONFIG_RESULT_H

#include "../../common/utils/game.h"

typedef struct
{
    char *delim;
    unsigned int lignes;
    unsigned int colonnes;
    char **table;
}CSV;

void open_csv(char *filename);
int suppr_csv(CSV * csv);
CSV* csv_esp_mem(unsigned int colonnes, unsigned int lignes);
int csv_ecriture_seule(CSV* csv,char *filename);
void write_header(char *filename);
void write_line(char *filename,Game);

#endif
