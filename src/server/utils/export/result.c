#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "result.h"
#include <stdbool.h>


/**
 * @brief  Crée et ouvre le fichier csv de nom *filename en paramètre
 * @note   
 * @param  *filename: 
 * @retval None
 */
void open_csv(char *filename){

    FILE *file;

    filename=strcat(filename,".csv");

    file = fopen(filename,"w");
}


/**
 * @brief  
 * @note   
 * @param  *filename: 
 * @retval None
 */
void write_header(const char *filename){

    FILE* file = fopen(filename,"a+");
    
    if(file != NULL){
        fprintf(file,"client_id;react_time;bet;balance;current_round;total_rounds;action\n");        
    }else{
        printf("Error writing header\n");
        
    }
    fclose(file);
}


/**
 * @brief  
 * @note   
 * @param  *filename: 
 * @param  data: 
 * @retval None
 */
void write_line(const char *filename,Game *data,int client_id) {

    FILE* file = fopen(filename,"a+");

    if(file != NULL){
        char action[15];
        switch (data->action)
        {
        case BETRAY:{
            strcpy(action,"BETRAY");
            break;
        }
        case COLLABORATE:{
            strcpy(action,"COLLABORATE");
            break;
        }
        }
        fprintf(file,"%d;%.3f;%d;%d;%d;%d;%s\n",client_id,data->react_time / 1000,data->bet,data->balance,data->current_round,data->total_rounds,action);
    }
    fclose(file);
}