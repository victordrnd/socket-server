#include "actions.h"
#include "communication.h"

void on_connect_action(Encapsulation *packet){
    Connected_data data;
    data.initial_balance = 100;
    send_packet(packet->sender_id, CONNECTED, &data, sizeof(Connected_data));
}


void settle_action(Encapsulation *packet){

    switch (packet->action)
    {
    case CONNECT: {
        on_connect_action(packet);
        break;
    }
    default:
        break;
    }
}