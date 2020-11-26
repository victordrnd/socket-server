/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#ifndef S_ACTIONS_HEADER_H
#define S_ACTIONS_HEADER_H
#include <stdbool.h>
#include "../../common/protocol/protocol.h"
#include "../utils/config.h"
#include "../../common/game.h"
typedef struct{
    unsigned int client_id;
    Game *game;
} Session;


void on_connect_action(Encapsulation *packet);
void on_disconnect_action(Encapsulation *packet);
void send_game_start(Encapsulation *packet, Room* room);
void send_round_start(unsigned int client_id, Room *room);
void settle_action(Encapsulation *packet);
bool check_oppponent_connected(unsigned int client_id);
Session *check_opponent_played(unsigned int opponent_id);
void check_results(Game *, Game *opponnent_game, unsigned int client_id, unsigned int opponent_id);
void send_game_end(unsigned int client_id, enum results winner);
#endif