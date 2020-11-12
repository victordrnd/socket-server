#include <stdlib.h>
#include <libconfig.h>
#include <assert.h>
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

    printf("\n Creating %s.csv file",filename);
    FILE *file;

    filename=strcat(filename,".csv");

    file = fopen(filename,"w");

    if(file == NULL){
        printf("Fichier pas trouvé, création en cours\n");
    }else{
        printf("Fichier créé, prêt à êre utilisé\n");
        fclose(file);
    }   
}


/**
 * @brief  
 * @note   
 * @param  *filename: 
 * @retval None
 */
void write_header(char *filename){

    FILE* file = fopen(filename,"a+");
    
    if(file != NULL){
        fprintf(file,"react_time;bet;balance;current_round;total_rounds;action\n");
        printf("writing header\n");
        
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
void write_line(char *filename,Game *data) {

    FILE* file = fopen(filename,"a+");

    if(file != NULL){
        fprintf(file,"%d;%d;%d;%d;%d;%d\n",data->react_time,data->bet,data->balance,data->current_round,data->total_rounds,data->action);

    }else{
        printf("Error writing header\n");
    }
    fclose(file);
}