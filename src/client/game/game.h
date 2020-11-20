#ifndef GAME_HEADER_FILE_H
#define GAME_HEADER_FILE_H
#include <stdbool.h>
#include <sys/time.h>
#include "../../common/game.h"

void init_game(Game *game);
void game_set_current_bet(unsigned int bet);
int game_get_current_bet();
void game_set_balance(unsigned int balance);
void game_set_action(enum actions action);
void game_set_max_rounds(unsigned int maxrounds);
bool game_next_round();
void game_set_react_time(struct timeval round_start_time, struct timeval action_clicked_time);
Game *get_game();
void set_game(Game *);
#endif