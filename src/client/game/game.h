#ifndef GAME_HEADER_FILE_H
#define GAME_HEADER_FILE_H
#include "../../common/game.h"

void init_game(Game *game);
void game_set_current_bet(unsigned int bet);
int game_get_current_bet();
void game_set_action(enum actions action);
#endif