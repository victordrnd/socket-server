#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include "logs.h"
#include "fort.h"
void debug_print_f(char *fm, ...)
{
    time_t t = time(NULL);

    va_list arg;
    va_start(arg, fm);

    struct tm tm = *localtime(&t);
    printf("\033[0;34m[%d-%02d-%02d %02d:%02d:%02d] \033[0m", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    while (*fm != '\0')
    {
        if (*fm != '%')
        {
            putchar(*fm);
            fm++;
            continue;
        }

        fm++;

        if (*fm == '\0')
        {
            break;
        }

        switch (*fm)
        {
        case 's':
            fputs(va_arg(arg, char *), stdout);
            break;
        case 'c':
            putchar(va_arg(arg, int));
            break;
        case 'd':
            printf("%d",va_arg(arg, int));
            break;
        }
        fm++;
    }

    va_end(arg);
}

void debug_print_client_config_f(unsigned int client_id, const char *server_ip, unsigned int port)
{
#ifndef NDEBUG
    ft_table_t *table = ft_create_table();
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(table, "Client ID", "Server IP", "Port");
    ft_printf_ln(table, "%d|%s|%d", client_id, server_ip, port);
    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
#endif
}

void debug_print_server_config_f(const char *bind_ip, unsigned int port, unsigned int max_cnx)
{
#ifndef NDEBUG
    ft_table_t *table = ft_create_table();
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(table, "Bind IP", "Port", "Max connections");
    ft_printf_ln(table, "%s|%d|%d", bind_ip, port, max_cnx);
    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
#endif
}
