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

/**
 * @brief Encapsulate data in a packet to send
 * 
 * @param packet 
 * @param sender_id 
 * @param destionation_id 
 * @param verb 
 * @param data 
 * @param data_size 
 */
void encapsulate_data(Encapsulation *packet, __uint32_t sender_id, __uint32_t destionation_id, enum verbs verb, void *data, size_t data_size)
{
    if(destionation_id > 0){
        sender_id = 0;
    }
    assert(data_size <= MAXPACKETSIZE);
    packet->sender_id = sender_id;
    packet->destination_id = destionation_id;
    packet->timestamp = time(NULL);
    packet->action = verb;
    packet->sizeof_data = data_size;
    if (data != NULL)
    {
        memcpy(packet->data, (const unsigned char *)data, data_size);
    }
}
