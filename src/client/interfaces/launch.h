/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#ifndef LAUNCH_HEADER_H
#define LAUNCH_HEADER_H

#include <gtk/gtk.h>

void init_main_window(int argc, char **argv);
void close_main_window(gboolean is_cnx_closed);
#endif