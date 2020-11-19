#include "game.h"
#include "../utils/config.h"
#include <time.h>
Game *game;

/**
 * @brief Init current game
 * 
 * @param c_game game to initialized
 * @param config Client configuration
 */
void init_game(Game *c_game){
    game = c_game;
    game->action = NOACTION;
    game->balance = 100; 
    game->bet = 10;
    game->current_round = 1; 
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
int game_get_current_bet(){
    return game->bet;
}

bool game_next_round(){
    return ++(game->current_round) <= game->total_rounds;
}

void game_set_action(enum actions action){
    game->action = action;
}


void game_set_react_time(clock_t round_start_time, clock_t action_clicked_time){
    game->react_time = action_clicked_time - round_start_time;
}
void game_set_max_rounds(unsigned int maxrounds){
    game->total_rounds = maxrounds;
}

Game *get_game(){
    return game;
}
void set_game(Game *game_v){
    game = game_v;
}

void game_set_balance(unsigned int balance){
    game->balance = balance;;
}