#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "protocol.h"
#include "game.h"

void parse_verbs_data(Encapsulation *encapsulation)
{
    switch (encapsulation->action)
    {
        case CONNECT : //

            break;
            
        case CONNECTED : //Renvoi la cagnotte inital et le nom de l'adversaire

            Game *dataGame = encapsulation->binary;

            break;
        
        case FAILED : //renvoi null

            *encapsulation->binary = NULL;

            break;
        
        case GAME_START :
            
            break;
        
        case ROUND_START :
            
            break;

        case ACTION :
            
            break;    
        
        case ROUND_END :
            
            break;

        case GAME_END :
            
            break;

        case DISCONNECT :
            
            break;    
    }


}


