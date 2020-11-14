#include "actions.h"
#include "../interfaces/handlers/handlers.h"
void settle_action(Encapsulation *packet){
     
    switch (packet->action)
    {
    case CONNECTED:{
        Connected_data *data = (Connected_data *) packet->data;
        printf("balance :%d\n", data->initial_balance);
        on_connected_action(packet->data);
        break;
    }
    
    default:
        break;
    }
}