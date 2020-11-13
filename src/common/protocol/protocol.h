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
    unsigned int sender_id;         
    unsigned int destination_id;
    time_t timestamp;              //nb secondes depuis 01/01/1970 38237283723 
    enum verbs action;
    double protocol_version;    
    size_t sizeof_data;
    int data[];

} Encapsulation;

void parse_verbs_data(Encapsulation *encapsulation);

#endif

