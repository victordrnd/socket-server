/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include <stdio.h>
#include <assert.h>

#include "actions.h"
#include "communication.h"
#include "../../common/tests/logs/logs.h"
#include "../utils/config.h"
#include "../utils/export/result.h"

Session *sessions[MAXSIMULTANEOUSCLIENTS];

void add_session(Session *session)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        if (sessions[i] == NULL)
        {
            sessions[i] = session;
            return;
        }
    }
    assert(false);
}

void remove_session(Session *session)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        if (session == sessions[i])
        {
            sessions[i] = NULL;
            return;
        }
    }
    assert(false);
}

void on_connect_action(Encapsulation *packet)
{
    Room *room = get_client_room(packet->sender_id);
    if (room != NULL)
    {
        Connected_data data = {.initial_balance = get_initial_amount(room)};
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
        debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mFAILED\033[0m to \033[1;32m#%d\033[0m.\n", packet->sender_id);
    }
}

void send_game_start(Encapsulation *packet, Room *room)
{
    Game_Start_data data = {.max_rounds = get_max_round_count(room),
                            .initial_balance = (unsigned int)get_initial_amount(room)};
    send_packet(packet->sender_id, GAME_START, &data, sizeof(Game_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mGAME_START\033[0m to \033[1;32m#%d\033[0m.\n", packet->sender_id);

    int opponent = get_opponent_id(packet->sender_id);
    send_packet(opponent, GAME_START, &data, sizeof(Game_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mGAME_START\033[0m to \033[1;32m#%d\033[0m.\n", opponent);

    send_round_start(packet->sender_id);
    send_round_start(opponent);

    create_csv_result_file((char *)room->name);
}

void send_round_start(unsigned int client_id)
{
    Round_Start_data data = {.round_duration = 3};
    send_packet(client_id, ROUND_START, &data, sizeof(Round_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mROUND_START\033[0m to \033[1;32m#%d\033[0m.\n", client_id);
}

void send_round_end(unsigned int client_id, Game *game)
{
    send_packet(client_id, ROUND_END, game, sizeof(Game));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mROUND_END\033[0m to \033[1;32m#%d\033[0m. %d/%d\n", client_id, game->current_round, game->total_rounds);
}

void on_action_received(Encapsulation *packet)
{
    Game *game = (Game *)packet->data;
    unsigned int opponent_id = get_opponent_id(packet->sender_id);
    Session *opponent_session = check_opponent_played(opponent_id);
    if (opponent_session != NULL)
    {
        Game *opponnent_game = opponent_session->game;
        if (game->action == BETRAY)
        {
            if (opponnent_game->action == BETRAY)
            { //J1 Trahi et J2 Trahi
                game->balance -= game->bet;
                opponnent_game->balance -= opponnent_game->bet;
            }
            else
            { //J1 Trahi et J2 Collaborate
                game->balance += game->bet;
                opponnent_game->balance -= opponnent_game->bet;
            }
        }
        else
        {
            if (opponnent_game->action == BETRAY)
            { //J1 Collabore et J2 Trahi
                game->balance -= game->bet;
                opponnent_game->balance += opponnent_game->bet;
            }else // Les deux collaborent
            {
                game->balance += game->bet /2;
                opponnent_game->balance += opponnent_game->bet /2;
            }
        }
        Room *room = get_client_room(packet->sender_id);
        write_line(room->name, game, packet->sender_id);
        write_line(room->name, opponnent_game, opponent_session->client_id);
        game->action = NOACTION;
        opponnent_game->action = NOACTION;
        send_round_end(packet->sender_id, game);
        send_round_end(opponent_id, opponnent_game);
        remove_session(opponent_session);
        if (game->current_round < get_max_round_count(room))
        {
            send_round_start(packet->sender_id);
            send_round_start(opponent_id);
        }
        else
        {
            check_results(game, opponnent_game, packet->sender_id, opponent_id);
        }
    }
    else
    {
        Session current_session = {packet->sender_id, game};
        add_session(&current_session);
    }
}

void check_results(Game *game, Game *opponnent_game, unsigned int client_id, unsigned int opponent_id)
{

    if (game->balance > opponnent_game->balance)
    {
        send_game_end(client_id, VICTORY);
        send_game_end(opponent_id, DEFEAT);
    }
    else if (game->balance < opponnent_game->balance)
    {
        send_game_end(client_id, DEFEAT);
        send_game_end(opponent_id, VICTORY);
    }
    else
    {
        send_game_end(client_id, EQUALITY);
        send_game_end(opponent_id, EQUALITY);
    }
}
void send_game_end(unsigned int client_id, enum results winner)
{
    Game_End_data data = {.result = winner};
    send_packet(client_id, GAME_END, &data, sizeof(Game_End_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mGAME_END\033[0m to \033[1;32m#%d\033[0m.\n", client_id);
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
    return false;
}

Session *check_opponent_played(unsigned int opponent_id)
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

void on_disconnect_action ( Encapsulation *packet){
    
}