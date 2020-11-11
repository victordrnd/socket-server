#ifndef PROTOCOL_H
#define PROTOCOL_H

enum verbs{
    CONNECT = 0x10,
    CONNECTED = 0x11,
    GAME_START = 0x12,
    ROUND_START = 0x13,
    ROUND_END = 0x14,
    GAME_END = 0x15,
    DISCONNECT = 0x16

};

#endif