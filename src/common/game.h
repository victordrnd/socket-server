/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

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

