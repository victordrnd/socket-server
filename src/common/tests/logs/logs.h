/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#ifndef LOG_HEADER_H 
#define LOG_HEADER_H
#ifndef NDEBUG
    #define debug_print(...) debug_print_f(__VA_ARGS__)
    #define debug_print_client_config(...) debug_print_client_config_f(__VA_ARGS__)
    #define debug_print_server_config(...) debug_print_server_config_f(__VA_ARGS__)
#else
    #define void_f do {} while(0)
    #define debug_print(...) void_f
    #define debug_print_client_config(...) void_f
    #define debug_print_server_config(...) void_f
#endif
void debug_print_f(const char * fm, ...);
void debug_print_client_config_f(unsigned int client_id, const char *server_ip, unsigned int port);


void debug_print_server_config_f(const char * bind_ip, unsigned int port, unsigned int max_cnx);
#endif