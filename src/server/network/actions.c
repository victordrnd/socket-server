#include <stdio.h>
#include "actions.h"
#include "communication.h"
#include "../../common/tests/logs/logs.h"
#include "../utils/config.h"

Session *sessions[MAXSIMULTANEOUSCLIENTS];

void on_connect_action(Encapsulation *packet)
{
    Connected_data data;
    Room *room = get_client_room(packet->sender_id);
    if (room != NULL)
    {
        data.initial_balance = get_initial_amount(room);
        send_packet(packet->sender_id, CONNECTED, &data, sizeof(Connected_data));
        debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mCONNECTED\033[0m to \033[1;32m#%d\033[0m.\n", packet->sender_id);
        if (check_oppponent_connected(packet->sender_id))
        {
            send_game_start(packet, room);
        }
    }
    else
    {
        send_packet(packet->sender_id, FAILED, NULL, 0);
        connection_t *cnx = get_connection(packet->sender_id);
        del(cnx);
        debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mFAILED\033[0m to \033[1;32m#%d\033[0m.\n", packet->sender_id);
    }
}

void send_game_start(Encapsulation *packet, Room *room)
{
    Game_Start_data data = {get_max_round_count(room), (unsigned int)get_initial_amount(room)};
    send_packet(packet->sender_id, GAME_START, &data, sizeof(Game_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mGAME_START\033[0m to \033[1;32m#%d\033[0m.\n", packet->sender_id);

    int opponent = get_opponent_id(packet->sender_id);
    send_packet(opponent, GAME_START, &data, sizeof(Game_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mGAME_START\033[0m to \033[1;32m#%d\033[0m.\n", opponent);

    send_round_start(packet->sender_id, opponent);
}

void send_round_start(int client1, int client2)
{
    Round_Start_data data = {10};
    send_packet(client1, ROUND_START, &data, sizeof(Round_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mROUND_START\033[0m to \033[1;32m#%d\033[0m.\n", client1);
    send_packet(client2, ROUND_START, &data, sizeof(Round_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mROUND_START\033[0m to \033[1;32m#%d\033[0m.\n", client2);
}

void on_action_received(Encapsulation *packet)
{
    Game *game = (Game *)packet->data;
    unsigned int opponent_id = get_opponent_id(packet->sender_id);
    Session *opponent_session = check_if_opponent_played(opponent_id);
    if (opponent_session != NULL)
    {
        Game *opponnent_game = opponent_session->game;
        //Process results
    }
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

    case DISCONNECT:
    {

        break;
    }
    case ACTION:
    {
        debug_print("\033[1;32m#%d\033[0m sent \033[0;32mACTION\033[0m action.\n", packet->sender_id);
        on_action_received(packet);
        break;
    }
    default:
        break;
    }
}

bool check_oppponent_connected(unsigned int client_id)
{
    if (get_opponent_id(client_id) > 0)
    {
        int opponent = get_opponent_id(client_id);
        return get_connection(opponent) != NULL;
    }
}

Session *check_if_opponent_played(unsigned int opponent_id)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        if (sessions[i] != NULL)
        {
            if (sessions[i]->client_id == opponent_id)
                return sessions[i];
        }
    }
    return NULL;
}