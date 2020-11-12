#ifndef PROTOCOL_H
#define PROTOCOL_H

enum verbs{

    CONNECT = 0x10,             //Hexadecimal : pour plus de sécurité au niveau des trames et optimise la mémoire 
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

    char sender_id[30];         //id du client
    char destination_id[30];    //
    int timestamp;              //nb secondes depuis 01/01/1970 38237283723 
    enum verbs action;          //encapsulation de enum vers
    char binary[2048];          //buffer de mise et choix
    double protocol_version;    

} Encapsulation;

void parse_verbs_data(Encapsulation *encapsulation);

#endif

