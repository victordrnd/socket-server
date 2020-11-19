#ifndef S_ACTIONS_HEADER_H
#define S_ACTIONS_HEADER_H
#include <stdbool.h>
#include "../../common/protocol/protocol.h"
void settle_action(Encapsulation *packet);
bool check_oppponent_connected(unsigned int client_id);

#endif