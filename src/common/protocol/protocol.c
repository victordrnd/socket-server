#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "protocol.h"
#include "../game.h"


Encapsulation encapsulate_data(__uint32_t sender_id,__uint32_t destionation_id, enum verbs verb, void *data){
    if(sender_id > 0){
        destionation_id = 0; //0 is server
    }

    __uint8_t *buffer=(__uint8_t*) malloc(sizeof(data));
    memcpy(buffer,(const __uint8_t*)&data,sizeof(data));

    Encapsulation encapsulation;
    encapsulation.sender_id = sender_id;
    encapsulation.destination_id = destionation_id;
    encapsulation.timestamp = time(NULL);
    encapsulation.action = verb;
    encapsulation.data[sizeof(data)] = *((__uint8_t *) buffer);
    free(buffer);
    return encapsulation;
}


void unwrap_data(__uint8_t *recv_data, size_t recv_size){
    if (recv_size < sizeof(Encapsulation)) {
        //received data too small
        return;
    }
    Encapsulation *recv_packet = (Encapsulation *)recv_data;
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


