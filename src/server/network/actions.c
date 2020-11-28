/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

#include "actions.h"
#include "communication.h"
#include "../../common/tests/logs/logs.h"
#include "../utils/config.h"
#include "../utils/export/result.h"

Session *sessions[MAXSIMULTANEOUSCLIENTS];

/**
 * @brief Add round session
 * 
 * @param session data from this round to be saved
 */
void add_session(Session *session)
{
    assert(session);
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

/**
 * @brief Remove round session 
 * 
 * @param session session to remove
 */
void remove_session(Session *session)
{
    assert(session);
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

/**
 * @brief Execute connect action
 * 
 * @param packet 
 */
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

/**
 * @brief Send game start packet
 * 
 * @param packet 
 * @param room 
 */
void send_game_start(Encapsulation *packet, Room *room)
{
    Game_Start_data data = {.max_rounds = get_max_round_count(room),
                            .initial_balance = (unsigned int)get_initial_amount(room)};
    send_packet(packet->sender_id, GAME_START, &data, sizeof(Game_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mGAME_START\033[0m to \033[1;32m#%d\033[0m.\n", packet->sender_id);

    int opponent = get_opponent_id(packet->sender_id);
    send_packet(opponent, GAME_START, &data, sizeof(Game_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mGAME_START\033[0m to \033[1;32m#%d\033[0m.\n", opponent);

    send_round_start(packet->sender_id, room);
    send_round_start(opponent, room);

    create_csv_result_file((char *)room->name);
}

/**
 * @brief Send round start packet
 * 
 * @param client_id 
 * @param room 
 */
void send_round_start(unsigned int client_id, Room *room)
{
    Round_Start_data data = {.waiting_time = room->waiting_time};
    send_packet(client_id, ROUND_START, &data, sizeof(Round_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mROUND_START\033[0m to \033[1;32m#%d\033[0m.\n", client_id);
}

/**
 * @brief Send round end packet
 * 
 * @param client_id 
 * @param game 
 */
void send_round_end(unsigned int client_id, Game *game)
{
    send_packet(client_id, ROUND_END, game, sizeof(Game));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mROUND_END\033[0m to \033[1;32m#%d\033[0m. %d/%d\n", client_id, game->current_round, game->total_rounds);
}

/**
 * @brief Execute action's action
 * 
 * @param packet 
 */
void on_action_received(Encapsulation *packet)
{
    Game *game = (Game *)packet->data;
    unsigned int opponent_id = get_opponent_id(packet->sender_id);
    Session *opponent_session = check_opponent_played(opponent_id);
    if (opponent_session != NULL)
    {
        Game *opponent_game = opponent_session->game;
        calculate_balance(game, opponent_game);
        Room *room = get_client_room(packet->sender_id);
        write_line(room->name, game, packet->sender_id);
        write_line(room->name, opponent_game, opponent_session->client_id);
        send_round_end(packet->sender_id, game);
        send_round_end(opponent_id, opponent_game);
        remove_session(opponent_session);
        if (game->current_round < get_max_round_count(room))
        {
            send_round_start(packet->sender_id, room);
            send_round_start(opponent_id, room);
        }
        else
        {
            check_results(game, opponent_game, packet->sender_id, opponent_id);
        }
    }
    else
    {
        Session current_session = {packet->sender_id, game};
        add_session(&current_session); //save current player game awaiting opponent game.
    }
}

/**
 * @brief Calculate players balance based on current round data
 * 
 * @param game 
 * @param opponent_game 
 */
void calculate_balance(Game *game, Game *opponent_game){
    if (game->action == BETRAY)
        {
            if (opponent_game->action == BETRAY)
            { //J1 Trahi et J2 Trahi
                game->balance -= game->bet;
                opponent_game->balance -= opponent_game->bet;
            }
            else
            { //Collaborate
                game->balance += game->bet;
                opponent_game->balance -= opponent_game->bet;
            }
        }
        else
        {
            if (opponent_game->action == BETRAY)
            { //J1 Collabore et J2 Trahi
                game->balance -= game->bet;
                opponent_game->balance += opponent_game->bet;
            }
        }
}
/**
 * @brief Check who won the game between client_id and opponent_id
 * 
 * @param game 
 * @param opponent_game 
 * @param client_id 
 * @param opponent_id 
 */
void check_results(Game *game, Game *opponent_game, unsigned int client_id, unsigned int opponent_id)
{

    if (game->balance > opponent_game->balance)
    {
        send_game_end(client_id, VICTORY);
        send_game_end(opponent_id, DEFEAT);
    }
    else if (game->balance < opponent_game->balance)
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

/**
 * @brief Send Game End packet
 * 
 * @param client_id 
 * @param winner 
 */
void send_game_end(unsigned int client_id, enum results winner)
{
    Game_End_data data = {.result = winner};
    send_packet(client_id, GAME_END, &data, sizeof(Game_End_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mGAME_END\033[0m to \033[1;32m#%d\033[0m.\n", client_id);
}

/**
 * @brief Execute disconnect action
 * 
 * @param packet 
 */
void on_disconnect_action(Encapsulation *packet)
{
    debug_print("\033[1;32m#%d\033[0m Connection to client ended\n", packet->sender_id);
    connection_t* connection = get_connection(packet->sender_id);
    close(connection->sockfd);
    del(connection);
    free(connection);
    pthread_exit(0);
}


/**
 * @brief Execute action based on packet's action
 * 
 * @param packet 
 */
void settle_action(Encapsulation *packet)
{
    assert(packet);
    switch (packet->action)
    {
    case CONNECT:
    {
        debug_print("\033[1;32m#%d\033[0m sent \033[0;32mCONNECT\033[0m action.\n", packet->sender_id);
        on_connect_action(packet);
        break;
    }

    case ACTION:
    {
        debug_print("\033[1;32m#%d\033[0m sent \033[0;32mACTION\033[0m action.\n", packet->sender_id);
        on_action_received(packet);
        break;
    }

    case DISCONNECT:
    {
        debug_print("\033[1;32m#%d\033[0m sent \033[0;32mDISCONNECT\033[0m action.\n", packet->sender_id);
        on_disconnect_action(packet);
        break;
    }

    default:
        break;
    }
}

/**
 * @brief Check if opponent is connected
 * 
 * @param client_id 
 * @return true 
 * @return false 
 */
bool check_oppponent_connected(unsigned int client_id)
{
    if (get_opponent_id(client_id) > 0)
    {
        int opponent = get_opponent_id(client_id);
        return get_connection(opponent) != NULL;
    }
    return false;
}

/**
 * @brief Check if opponent has played for current round
 * 
 * @param opponent_id 
 * @return Session* 
 */
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

