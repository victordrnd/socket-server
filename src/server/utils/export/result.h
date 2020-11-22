/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#ifndef SRC_SERVER_UTILS_EXPORT_RESULT_H_
#define SRC_SERVER_UTILS_EXPORT_RESULT_H_

#include "../../../common/game.h"

void create_csv_result_file(char *filename);

void write_line(const char *filename,Game *data,int client_id);

#endif // SRC_SERVER_UTILS_EXPORT_RESULT_H_
