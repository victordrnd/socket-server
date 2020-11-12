#ifndef PROTOCOL_H
#define PROTOCOL_H

enum verbs{

    CONNECT = 0x10, //Hexadecimal : pour plus de sécurité au niveau des trames et optimise la mémoire 
    CONNECTED = 0x11,
    FAILED = 0x12,
    GAME_START = 0x13,
    ROUND_START = 0x14,
    ROUND_END = 0x15,
    GAME_END = 0x16,
    DISCONNECT = 0x17
};

typedef struct {

    int sender_id;
    int destination_id;
    int timestamp;
    enum verbs action;
    char binary[2048];

} Encapsulation;

void parse_verbs_data(Encapsulation *encapsulation);

#endif

