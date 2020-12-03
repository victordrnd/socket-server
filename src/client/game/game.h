/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#ifndef SRC_CLIENT_GAME_GAME_H_
#define SRC_CLIENT_GAME_GAME_H_
#include <stdbool.h>
#include <sys/time.h>
#include "../../common/game.h"

Game* init_game(void);
void game_set_current_bet(unsigned int bet);
void game_set_balance(unsigned int balance);
void game_set_action(enum actions action);
void game_set_max_rounds(unsigned int maxrounds);
void game_set_react_time(struct timeval round_start_time, struct timeval action_clicked_time);
int game_get_current_bet(void);
unsigned int game_get_balance(void);
bool game_next_round(void);
Game *get_game(void);
void set_game(Game *);
#endif // SRC_CLIENT_GAME_GAME_H_