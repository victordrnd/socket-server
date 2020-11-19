#include <stdio.h>
#include "actions.h"
#include "communication.h"
#include "../../common/tests/logs/logs.h"
#include "../utils/config.h"
#include "../utils/export/result.h"

Session *sessions[MAXSIMULTANEOUSCLIENTS];

void add_session(Session *session){
    for(int i=0; i < MAXSIMULTANEOUSCLIENTS; i++){
        if(sessions[i] == NULL){
            sessions[i] = session;
            continue;
        }
    }
}

void remove_session(Session *session){
    for(int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++){
        if(session == sessions[i]){
            sessions[i] = NULL;
            continue;
        }
    }
}

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

    send_round_start(packet->sender_id);
    send_round_start(opponent);


    open_csv(room->name);
    write_header(room->name);
}

void send_round_start(unsigned int client_id)
{
    Round_Start_data data = {10};
    send_packet(client_id, ROUND_START, &data, sizeof(Round_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mROUND_START\033[0m to \033[1;32m#%d\033[0m.\n", client_id);
}

void send_round_end(unsigned int client_id, Game *game)
{
    send_packet(client_id, ROUND_END, game, sizeof(Game));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mROUND_END\033[0m to \033[1;32m#%d\033[0m.\n", client_id);
}

void on_action_received(Encapsulation *packet)
{
    Game *game = (Game *)packet->data;
    unsigned int opponent_id = get_opponent_id(packet->sender_id);
    Session *opponent_session = check_if_opponent_played(opponent_id);
    if (opponent_session != NULL)
    {
        Game *opponnent_game = opponent_session->game;
        if (game->action == BETRAY)
        {
            if (opponnent_game->action == BETRAY)
            {
                game->balance -= game->bet;
                opponnent_game->balance -= game->bet;
            }
            else
            { //Collaborate
                game->balance += opponnent_game->bet;
                opponnent_game->balance -= opponnent_game->bet;
            }
        }
        else
        {
            if (opponnent_game->action == BETRAY)
            {
                game->balance -= game->bet;
                opponnent_game->balance += game->bet;
            }
        }
        Room *room = get_client_room(packet->sender_id);
        game->action = NOACTION;
        opponnent_game->action = NOACTION;
        game->total_rounds = get_max_round_count(room);
        opponnent_game->total_rounds = get_max_round_count(room);
        write_line(room->name, game, packet->sender_id);
        write_line(room->name, opponnent_game,opponent_session->client_id);
        send_round_end(packet->sender_id, game);
        send_round_end(opponent_id, game);
        remove_session(opponent_session);
        printf("max round : %d\n", get_max_round_count(room));
        if(game->current_round < get_max_round_count(room)){
            send_round_start(packet->sender_id);
            send_round_start(opponent_id);
        }
    }else{
        Session current_session = {packet->sender_id,game};
        add_session(&current_session);
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