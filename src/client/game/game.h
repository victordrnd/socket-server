#ifndef GAME_HEADER_FILE_H
#define GAME_HEADER_FILE_H
#include "../utils/config.h"

enum actions
{
    BETRAY = 0x10,
    COLLABORATE = 0x11
};

typedef struct
{
    int balance;
    int currentBet;
    enum actions action;
    int round;
} Game;

void init_game(Game *game, Config *config);
void game_set_current_bet(int bet);
int game_get_current_bet();

#endif