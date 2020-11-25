/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include "game.h"
#include "../utils/config.h"

Game *game;

/**
 * @brief Init current game
 * 
 * @param c_game game to initialized
 * @param config Client configuration
 */
Game * init_game(Game *c_game){
    game = c_game;
    game->action = NOACTION;
    game->balance = 100; 
    game->bet = 10;
    game->current_round = 1; 
    return game;
}

/**
 * @brief Set current bet 
 * 
 * @param bet 
 */
void game_set_current_bet(unsigned int bet){
    game->bet = bet;
}

/**
 * @brief Get current bet
 * 
 * @return int 
 */
int game_get_current_bet(void){
    return game->bet;
}

bool game_next_round(void){
    if(game->current_round + 1 <= game->total_rounds) {
        game->current_round++;
        return true;
    }
    return false;
}

void game_set_action(enum actions action){
    game->action = action;
}


void game_set_react_time(struct timeval round_start_time, struct timeval action_clicked_time){
    game->react_time = (action_clicked_time.tv_sec - round_start_time.tv_sec) * 1000.0;
    game->react_time += (action_clicked_time.tv_usec - round_start_time.tv_usec) / 1000.0;
}

void game_set_balance(unsigned int balance){
    game->balance = balance;
}

void game_set_max_rounds(unsigned int maxrounds){
    game->total_rounds = maxrounds;
}

Game *get_game(void){
    return game;
}
void set_game(Game *game_v){
    game = game_v;
}
