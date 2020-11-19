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
void send_game_start(Encapsulation *packet, Room* room);
void send_round_start(int client1, int client2);
void on_action_received();
void settle_action(Encapsulation *packet);
bool check_oppponent_connected(unsigned int client_id);

#endif