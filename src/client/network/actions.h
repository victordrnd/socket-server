#ifndef ACTIONS_HEADER_H
#define ACTIONS_HEADER_H

#include "communication.h"
#include "../../common/game.h"

void settle_action(Encapsulation *packet);
void send_action_packet(Game *game);
#endif