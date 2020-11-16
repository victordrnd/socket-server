#ifndef LOG_HEADER_H 
#define LOG_HEADER_H

void debug_print(char * fm, ...);
char *convert(unsigned int num, int base);
void debug_print_client_config(unsigned int client_id, const char *server_ip, unsigned int port);
void debug_print_server_config(const char * bind_ip, unsigned int port, unsigned int max_cnx);
#endif