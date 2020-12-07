/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */
#include <stdlib.h>
#include "game.h"
#include "../utils/config.h"

Game *game;

/**
 * @brief Init current game
 * 
 * @param c_game game to initialized
 * @param config Client configuration
 */
Game * init_game(){
    game = (Game *)malloc(sizeof(Game));
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

/**
 * @brief  Get balance object
 * @note   
 * @retval 
 */
unsigned int game_get_balance(void){
    return game->balance;
}


/**
 * @brief Check if next round is allowed and increment current round count
 * 
 * @return true 
 * @return false 
 */
bool game_next_round(void){
    if(game->current_round + 1 <= game->total_rounds) {
        game->current_round++;
        return true;
    }
    return false;
}




/**
 * @brief Set Action code
 * 
 * @param action 
 */
void game_set_action(enum actions action){
    game->action = action;
}



/**
 * @brief Set round react time 
 * 
 * @param round_start_time 
 * @param action_clicked_time 
 */
void game_set_react_time(struct timeval round_start_time, struct timeval action_clicked_time){
    game->react_time = (action_clicked_time.tv_sec - round_start_time.tv_sec) * 1000.0;
    game->react_time += (action_clicked_time.tv_usec - round_start_time.tv_usec) / 1000.0;
}



/**
 * @brief Set game balance
 * 
 * @param balance 
 */
void game_set_balance(unsigned int balance){
    game->balance = balance;
}



/**
 * @brief Set game max round
 * 
 * @param maxrounds 
 */
void game_set_max_rounds(unsigned int maxrounds){
    game->total_rounds = maxrounds;
}



/**
 * @brief Get the game object
 * 
 * @return Game* 
 */
Game *get_game(void){
    return game;
}



/**
 * @brief Set the game object
 * 
 * @param game_v 
 */
void set_game(Game *game_v){
    game = game_v;
}
