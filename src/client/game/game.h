#ifndef GAME_HEADER_FILE_H
#define GAME_HEADER_FILE_H
#include <stdbool.h>
#include "../../common/game.h"

void init_game(Game *game);
void game_set_current_bet(unsigned int bet);
int game_get_current_bet();
void game_set_balance(unsigned int balance);
void game_set_action(enum actions action);
void game_set_max_rounds(unsigned int maxrounds);
bool game_next_round();
Game *get_game();
void set_game(Game *);
#endif