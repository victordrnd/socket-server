#include <stdbool.h>


#ifndef GAME_H
#define GAME_H

enum actions
{
    NOACTION,
    BETRAY,
    COLLABORATE
};

typedef struct {
    double react_time;
    unsigned int bet;
    unsigned int balance;
    unsigned int current_round;
    unsigned int total_rounds;
    enum actions action;
} Game;

#endif

