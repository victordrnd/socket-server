#include <stdbool.h>


#ifndef GAME_H
#define GAME_H

enum actions
{
    BETRAY,
    COLLABORATE
};

typedef struct {
    int react_time;
    int bet;
    int balance;
    int current_round;
    int total_rounds;
    enum actions action;
} Game;

#endif

