#include <stdio.h>
#include "actions.h"
#include "communication.h"
#include "../../common/tests/logs/logs.h"
#include "../utils/config.h"


void on_connect_action(Encapsulation *packet)
{
    Connected_data data;
    Room* room = get_client_room(packet->sender_id);
    data.initial_balance = get_initial_amount(room); //
    //TODO check if user in config + if not already connected

    send_packet(packet->sender_id, CONNECTED, &data, sizeof(Connected_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mCONNECTED\033[0m to \033[1;32m#%d\033[0m.\n", packet->sender_id);

    if (check_oppponent_connected(packet->sender_id))
    {
        send_game_start(packet,room);
    }
}

void send_game_start(Encapsulation *packet, Room* room){
    Game_Start_data data = {get_max_round_count(room), (unsigned int) get_initial_amount(room)};
    send_packet(packet->sender_id, GAME_START, &data, sizeof(Game_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mGAME_START\033[0m to \033[1;32m#%d\033[0m.\n", packet->sender_id);

    int opponent = get_opponent_id(packet->sender_id);
    send_packet(opponent, GAME_START, &data, sizeof(Game_Start_data));
    debug_print("\033[1;32mCONSOLE \033[0msent packet \033[0;32mGAME_START\033[0m to \033[1;32m#%d\033[0m.\n", opponent);
    
    send_round_start(packet->sender_id,opponent);
}

void send_round_start(int client1, int client2){
    Round_Start_data data = {10};
    send_packet(client1,ROUND_START,&data,sizeof(Round_Start_data));
    send_packet(client2,ROUND_START,&data,sizeof(Round_Start_data));

}

void on_action_receive(){
    
}

void settle_action(Encapsulation *packet)
{
    switch (packet->action)
    {
    case CONNECT:
    {
        debug_print("\033[1;32m#%d\033[0m sent \033[0;32mCONNECT\033[0m action.\n", packet->sender_id);
        on_connect_action(packet);
        break;
    }

    case DISCONNECT:
    {
        
        break;
    }
    default:
        break;
    }
}

bool check_oppponent_connected(unsigned int client_id)
{
    if (get_opponent_id(client_id) > 0)
    {
        int opponent = get_opponent_id(client_id);
        printf("%d\n", opponent);
        return get_connection(opponent) != NULL;
    }
}