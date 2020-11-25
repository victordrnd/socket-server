/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include "actions.h"
#include "../interfaces/handlers/handlers.h"
#include "../../common/protocol/protocol.h"


void send_action_packet(Game *game)
{
    send_packet(ACTION,game,sizeof(Game));
}

void send_disconnect_packet()
{
    send_packet(DISCONNECT, NULL, 0);
}

void settle_action(Encapsulation *packet)
{

    switch (packet->action)
    {
        case CONNECTED:
        {
            Connected_data *data = (Connected_data *) packet->data;
            on_connected_action(data);
            break;
        }

        case FAILED:
        {
            on_failed_action();
            break;
        }

        case GAME_START:
        {
            Game_Start_data *data = (Game_Start_data *) packet->data;
            on_game_start_action(data);
            break;
        }

        case ROUND_START:
        {
            Round_Start_data *data = (Round_Start_data *) packet->data;
            on_round_start_action(data);
            break;
        }
        case ROUND_END:
        {
            Game *data = (Game *) packet->data;
            on_round_end_action(data);       
            break;
        }
        case GAME_END:{
            Game_End_data *data = (Game_End_data *) packet->data;
            on_game_end_action(data);
            send_disconnect_packet();
            break;
        }
    
    }

}
