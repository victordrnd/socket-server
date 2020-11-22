/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#ifndef SRC_CLIENT_INTERFACES_HANDLERS_HANDLERS_H_
#define SRC_CLIENT_INTERFACES_HANDLERS_HANDLERS_H_

#include <gtk/gtk.h>
#include "../../../common/protocol/protocol.h"
#include "../../../common/game.h"

//Boutons radios
void on_mise_10_selected(GtkButton *button);
void on_mise_25_selected(GtkButton *button);
void on_mise_50_selected(GtkButton *button);
void on_mise_100_selected(GtkButton *button);

void on_betray_btn_click(GtkWidget *button __attribute__((unused)));
void on_collaborate_btn_click(GtkWidget *button __attribute__((unused)));

void on_connected_action(Connected_data *data);
void on_failed_action(void);
void on_game_start_action(Game_Start_data *data);
void on_round_start_action(Round_Start_data *data);
void on_round_end_action(Game *data);
void on_game_end_action(Game_End_data *data);

void gtk_set_builder(GtkBuilder *builder);
#endif // SRC_CLIENT_INTERFACES_HANDLERS_HANDLERS_H_