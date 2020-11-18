#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "protocol.h"
#include "../game.h"

void encapsulate_data(Encapsulation *encapsulation, __uint32_t sender_id, __uint32_t destionation_id, enum verbs verb, void *data, size_t data_size)
{
    if (sender_id > 0)
    {
        destionation_id = 0; //0 is server 
    }
    encapsulation->sender_id = sender_id;
    encapsulation->destination_id = destionation_id;
    encapsulation->timestamp = time(NULL);
    encapsulation->action = verb;
    //encapsulation->sizeof_data = data_size;
    if (data != NULL)
    {
        memcpy(encapsulation->data, (const unsigned char *)data, data_size);
    }
}

void parse_verbs_data(Encapsulation *encapsulation)
{
    switch (encapsulation->action)
    {
    case CONNECT:
    {

        break;
    }
    case CONNECTED:
    { //Renvoi la cagnotte inital et le nom de l'adversaire

        //Game *dataGame = (Game *) encapsulation->data;

        break;
    }
    case FAILED:
    {

        //encapsulation->data = NULL;

        break;
    }

    case GAME_START:
    {

        break;
    }
    case ROUND_START:
    {

        break;
    }
    case ACTION:
    {

        break;
    }
    case ROUND_END:
    {

        break;
    }
    case GAME_END:
    {

        break;
    }
    case DISCONNECT:
    {

        break;
    }
    }
}
