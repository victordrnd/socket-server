#include <stdbool.h>


#ifndef GAME_H
#define GAME_H

enum actions
{
    BETRAY = 0x10,
    COLLABORATE = 0x11
};

typedef struct {
    int tmpreact;
    int mise;
    int rest;
    bool stat;
    enum actions action;
} Choix;

#endif

