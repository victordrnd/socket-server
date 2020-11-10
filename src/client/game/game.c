#ifndef GAME_HEADER_H
#define GAME_HEADER_H
#include "game.h"
#include "../utils/config.h"

Game *game;

/**
 * @brief Init current game
 * 
 * @param c_game game to initialized
 * @param config Client configuration
 */
void init_game(Game *c_game, Config *config){
    game = c_game;
    //TODO get balance from server conf
    game->balance = 100; 
    game->currentBet = 10;
    game->round = 1; 
}

/**
 * @brief Set current bet 
 * 
 * @param bet 
 */
void game_set_current_bet(int bet){
    game->currentBet = bet;
}

/**
 * @brief Get current bet
 * 
 * @return int 
 */
int game_get_current_bet(){
    return game->currentBet;
}
#endif