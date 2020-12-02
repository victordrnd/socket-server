/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */
#include <gtk/gtk.h>

#include "actions.h"
#include "../interfaces/handlers/handlers.h"
#include "../../common/protocol/protocol.h"

/**
 * @brief Send connect packet to console
 * 
 */
void send_connect_packet(void)
{
    send_packet(CONNECT, NULL, (size_t)0);
}



/**
 * @brief Send round data
 * 
 * @param game 
 */
void send_action_packet(Game *game)
{
    send_packet(ACTION, game, sizeof(Game));
}



/**
 * @brief Send disconnect packet to console
 * 
 */
void send_disconnect_packet(void)
{
    send_packet(DISCONNECT, NULL, (size_t) 0);
}



/**
 * @brief Settle the packet based on action
 * 
 * @param packet 
 */
void settle_action(Encapsulation *packet)
{

    switch (packet->action)
    {
    case CONNECTED:
    {
        Connected_data *data = (Connected_data *)packet->data;
        g_idle_add((GSourceFunc) on_connected_action,data);
        break;
    }

    case FAILED:
    {
        g_idle_add((GSourceFunc) on_failed_action,NULL);
        break;
    }

    case GAME_START:
    {
        Game_Start_data *data = (Game_Start_data *)packet->data;
        g_idle_add((GSourceFunc) on_game_start_action,data);
        break;
    }

    case ROUND_START:
    {
        Round_Start_data *data = (Round_Start_data *)packet->data;
        g_idle_add((GSourceFunc) on_round_start_action, data);
        break;
    }
    case ROUND_END:
    {
        Game *data = (Game *)packet->data;
        g_idle_add((GSourceFunc) on_round_end_action,data);
        break;
    }
    case GAME_END:
    {
        Game_End_data *data = (Game_End_data *)packet->data;
        g_idle_add((GSourceFunc) on_game_end_action,data);
        send_disconnect_packet();
        break;
    }
    }
}
