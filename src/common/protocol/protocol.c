#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "protocol.h"
#include "../game.h"


Encapsulation encapsulate_data(unsigned int sender_id,unsigned int destionation_id, enum verbs verb, void *data){
    if(sender_id > 0){
        destionation_id = 0; //0 is server
    }
    Encapsulation encapsulation;
    encapsulation.sender_id = sender_id;
    encapsulation.destination_id = destionation_id;
    encapsulation.timestamp = time(NULL);
    encapsulation.action = verb;
    // encapsulation.data[sizeof(data)] = (int) *data;
    encapsulation.protocol_version = 1.0;
    return encapsulation;
}

void parse_verbs_data(Encapsulation *encapsulation)
{
    switch (encapsulation->action)
    {
        case CONNECT : {

            break;
        }
        case CONNECTED : { //Renvoi la cagnotte inital et le nom de l'adversaire

            //Game *dataGame = (Game *) encapsulation->data;

            break;
        }
        case FAILED :{

            //encapsulation->data = NULL;

            break;
        }
        
        case GAME_START : {
            
            break;
        }
        case ROUND_START : {
            
            break;
        }
        case ACTION : {
            
            break;    
        }
        case ROUND_END : {
            
            break;
        }
        case GAME_END : {
            
            break;
        }
        case DISCONNECT : {
            
            break;    
        }
    }


}


