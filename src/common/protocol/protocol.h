#ifndef PROTOCOL_H
#define PROTOCOL_H

enum verbs{
    CONNECT = 0x10,
    CONNECTED = 0x11,
    FAILED = 0x12,
    GAME_START = 0x13,
    ROUND_START = 0x14,
    ROUND_END = 0x15,
    GAME_END = 0x16,
    DISCONNECT = 0x17
};

#endif