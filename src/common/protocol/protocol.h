#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <time.h>


enum verbs{
    CONNECT = 0x10, //Offset de 16 car 0-16 réservé pour les actions (collaborate, betray)
    CONNECTED = 0x11,
    FAILED = 0x12,
    GAME_START = 0x13,
    ROUND_START = 0x14,
    ACTION = 0x15,
    ROUND_END = 0x16,
    GAME_END = 0x17,
    DISCONNECT = 0x18
};

typedef struct {
    __uint32_t sender_id;         
    __uint32_t destination_id;
    __uint64_t timestamp;              //nb secondes depuis 01/01/1970 38237283723 
    __uint32_t action;
    __int64_t sizeof_data;
    __uint8_t data[];
} __attribute__((packed)) Encapsulation;

void parse_verbs_data(Encapsulation *encapsulation);

#endif

