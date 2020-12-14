/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include "result.h"

/**
 * @brief  Write CSV header
 * @note   
 * @param  *filename: 
 * @retval None
 */
void write_header(const char *filename)
{
    FILE *file = fopen(filename, "a");
    assert(file != NULL);
    fprintf(file, "client_id;react_time;bet;balance;current_round;total_rounds;action\n");
    fclose(file);
    free(filename);
}

/**
 * @brief  Crée et ouvre le fichier csv de nom *filename en paramètre
 * @note   
 * @param  *filename: 
 * @retval None
 */
void create_csv_result_file(char *filename)
{
    char *file_name = (char*) malloc(strlen(filename) + 4);
    sprintf(file_name,"%s.csv", filename);
    FILE *file = fopen(file_name, "w");
    fclose(file);
    write_header(file_name);
}

/**
 * @brief  Write new result line in file
 * @note   
 * @param  *filename: 
 * @param  data: 
 * @retval None
 */
void write_line(const char *filename, Game *data, int client_id)
{
    char *file_name = (char*) malloc(strlen(filename) + 4);
    sprintf(file_name,"%s.csv", filename);
    FILE *file = fopen(file_name, "a");

    if (file != NULL)
    {
        char action[15];
        switch (data->action)
        {
        case BETRAY:
        {
            strcpy(action, "BETRAY");
            break;
        }
        case COLLABORATE:
        {
            strcpy(action, "COLLABORATE");
            break;
        }
        case NOACTION:
        {
            break;
        }
        }
        fprintf(file, "%d;%.3f;%d;%d;%d;%d;%s\n", client_id, data->react_time / 1000, data->bet, data->balance, data->current_round, data->total_rounds, action);
    }
    fclose(file);
    free(file_name);
}