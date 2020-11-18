#include "actions.h"
#include "../interfaces/handlers/handlers.h"



void settle_action(Encapsulation *packet){
     
    switch (packet->action)
    {
    case CONNECTED:{
        Connected_data *data = (Connected_data *) packet->data;
        on_connected_action(data);
        break;
    }

    case GAME_START:{
        
    }
    
    default:
        break;
    }
}