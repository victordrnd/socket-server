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
        Game_Start_data *data = (Game_Start_data *) packet->data;
        on_game_start_action(data);
        break;
    }

    case ROUND_START:{
        Round_Start_data *data = (Round_Start_data *) packet->data;
        on_round_start_action(data);
        break;
    }
    
    default:
        break;
    }
}