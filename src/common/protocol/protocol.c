/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "protocol.h"
#include "../game.h"

void encapsulate_data(Encapsulation *encapsulation, __uint32_t sender_id, __uint32_t destionation_id, enum verbs verb, void *data, size_t data_size)
{
    if(destionation_id > 0){
        sender_id = 0;
    }
    assert(data_size <= MAXPACKETSIZE);
    encapsulation->sender_id = sender_id;
    encapsulation->destination_id = destionation_id;
    encapsulation->timestamp = time(NULL);
    encapsulation->action = verb;
    encapsulation->sizeof_data = data_size;
    if (data != NULL)
    {
        memcpy(encapsulation->data, (const unsigned char *)data, data_size);
    }
}
