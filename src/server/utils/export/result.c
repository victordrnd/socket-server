/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "result.h"

/**
 * @brief  
 * @note   
 * @param  *filename: 
 * @retval None
 */
void write_header(const char *filename)
{
    FILE *file = fopen(filename, "a+");
    assert(file != NULL);
    fprintf(file, "client_id;react_time;bet;balance;current_round;total_rounds;action\n");
    fclose(file);
}

/**
 * @brief  Crée et ouvre le fichier csv de nom *filename en paramètre
 * @note   
 * @param  *filename: 
 * @retval None
 */
void create_csv_result_file(char *filename)
{
    filename = strcat(filename, ".csv");

    FILE *file = fopen(filename, "w");
    fclose(file);
    write_header(filename);
}

/**
 * @brief  
 * @note   
 * @param  *filename: 
 * @param  data: 
 * @retval None
 */
void write_line(const char *filename, Game *data, int client_id)
{

    FILE *file = fopen(filename, "a+");

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
}