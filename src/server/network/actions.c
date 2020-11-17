#include <stdio.h>
#include "actions.h"
#include "communication.h"
#include "../../common/tests/logs/logs.h"

void on_connect_action(Encapsulation *packet)
{
    Connected_data data;
    data.initial_balance = 100;
    //TODO check if user in config + if not already connected

    send_packet(packet->sender_id, CONNECTED, &data, sizeof(Connected_data));
    debug_print("\033[1;32m#%d \033[0mis sucessfully \033[0;32mCONNECTED.\n", packet->sender_id);
}

void settle_action(Encapsulation *packet)
{
    switch (packet->action)
    {
    case CONNECT:
    {
        debug_print("\033[1;32m#%d\033[0m sent \033[0;32mCONNECT\033[0m action.\n", packet->sender_id);
        on_connect_action(packet);
        break;
    }
    default:
        break;
    }
}