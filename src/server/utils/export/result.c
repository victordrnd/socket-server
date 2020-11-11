#include <stdlib.h>
#include <libconfig.h>
#include <assert.h>
#include <string.h>

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

    file = fopen(filename,"rt");
    if(file == NULL){
        printf("Fichier pas trouvé, création en cours");
        //Créer fichier
    }else{
        printf("Fichier ouvert, prêt à êre utilisé");
    }
}

/**
 * @brief  Supprime le ficiher csv en paramètre
 * @note   
 * @param  csv: 
 * @retval 
 */
int suppr_csv(CSV * csv) {
	if (csv == NULL) { return 0; }
	if (csv->table != NULL) { free(csv->table); }
	if (csv->delim != NULL) { free(csv->delim); }
	free(csv);
	return 0;
}

/**
 * @brief  Crée un emplacement memory pour le csv avec un tableau colonnes x lignes
 * @note   
 * @param  colonnes: 
 * @param  lignes: 
 * @retval 
 */
CSV* csv_esp_mem(unsigned int colonnes, unsigned int lignes){

    CSV*csv;
    csv=malloc(sizeof(CSV));
    csv->lignes=lignes;
    csv->colonnes=colonnes;
    csv->delim=strdup(";");
    csv->table=malloc(sizeof(char*)*colonnes*lignes);
    if(csv->table==NULL){goto erreur;}
    memset(csv->table,0,sizeof(char *)*colonnes*lignes);
    return csv;
 
    erreur:
        suppr_csv(csv);
        return NULL;
}


/**
 * @brief  
 * @note   
 * @param  csv: 
 * @param  *filename: 
 * @retval 
 */
int csv_ecriture_seule(CSV* csv,char *filename)
{
   FILE* fichier = fopen(filename,"w");
	if (fichier == NULL)
	{
		printf("Impossible a ouvrir: Erreur %d\n", filename);
		return -1;
	}
	else
	{
		// Succes
		int ret = csv_ecrire_fichierOuvert(csv, filename);
		fclose(filename);
		return ret;
	}
}

int csv_ecrire_fichierOuvert(CSV const * csv, FILE* fichier)
{
	/*Mettre le code d'écriture ici*/
    int ret = 0;



	return ret;
}

void write_header(char *filename){

    FILE* file = fopen(filename,"w");
    //Faire header tableau

}

void write_line(char *filename,Game data) {

    FILE* file = fopen(filename,"w");

    //Dernière ligne du csv

    fprintf(file,"%d",data);
    fclose(file);
}



/*main:
    CSV *nouveaucsv;
    nouveaucsv=csv_esp_mem(20,100);
    char fichier_name="rapport_1.csv";
    csv_ecriture_seule(nouveaucsv,fichier_name);
 
    int donnees;
    printf("entrez donnees:\n");
    scanf("%d",&donnees);
    ecrire_in_fichier_CSV(fichier,donnees);
    return 0;
*/