/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include <stdlib.h>
#include <string.h>
#include "network.h"

/**
 * @brief Verify if an ip is correctly formed
 * 
 * @param ip IP to verify
 * @return int 
 */
bool is_ip_valid(char *ip){
    int num, dots = 0;
    char *ptr;
    if (ip == NULL)
        return false;
    ptr = strtok(ip, ".");
    while (ptr){
        num = atoi(ptr);
        if (num >= 0 && num <= 255){
            ptr = strtok(NULL, ".");
            if (ptr != NULL)
                dots++;
        }
        else
            return false;
    }
    if (dots != 3)
        return false;
    return true;
}