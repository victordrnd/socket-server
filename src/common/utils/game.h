#include <stdbool.h>


#ifndef GAME_H
#define GAME_H

enum actions
{
    BETRAY = 0x10,
    COLLABORATE = 0x11
};

typedef struct {
    int react_time;
    int bet;
    int balance;
    enum actions action;
} Game;

#endif

