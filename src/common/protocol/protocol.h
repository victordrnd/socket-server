#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <time.h>



enum verbs{
    CONNECT = 0x10U, //Offset de 16 car 0-16 réservé pour les actions (collaborate, betray)
    CONNECTED = 0x11U,
    FAILED = 0x12U,
    GAME_START = 0x13U,
    ROUND_START = 0x14U,
    ACTION = 0x15U,
    ROUND_END = 0x16U,
    GAME_END = 0x17U,
    DISCONNECT = 0x18U
};

typedef struct {
    __uint32_t sender_id;         
    __uint32_t destination_id;
    __uint64_t timestamp;              //nb secondes depuis 01/01/1970 38237283723 
    __uint32_t action;
    __uint64_t sizeof_data;
    __uint8_t data[16];
} __attribute__((packed)) Encapsulation;


typedef struct{
    __uint32_t opponent_id;
    __uint32_t initial_balance;
} Connected_data;

typedef struct {
    __uint32_t max_rounds;
} Game_Start_data;

typedef struct {
    __uint32_t current_round;
    __uint32_t deadline;
} Round_Start_data;

typedef struct {
    __uint32_t balance;
} Round_End_data;

typedef struct {
    __uint32_t balance;
    __uint32_t max_rounds;
} Game_End_data;

void encapsulate_data(Encapsulation *encapsulation, __uint32_t sender_id,__uint32_t destionation_id, enum verbs verb, void *data, size_t data_size);
void parse_verbs_data(Encapsulation *encapsulation);

#endif

