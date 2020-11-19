#ifndef HANDLERS_H
#define HANDLERS_H

#include <gtk/gtk.h>
#include "../../../common/protocol/protocol.h"
//Boutons radios
void on_mise_10_selected(GtkButton *button, GtkBuilder *builder);
void on_mise_25_selected(GtkButton *button, GtkBuilder *builder);
void on_mise_50_selected(GtkButton *button, GtkBuilder *builder);
void on_mise_100_selected(GtkButton *button, GtkBuilder *builder);

void on_betray_btn_click(GtkWidget *button, GtkBuilder *builder);
void on_collaborate_btn_click(GtkWidget *button, GtkBuilder *builder);

void on_connected_action(Connected_data *data);
void on_game_start_action(Game_Start_data *data);
void on_round_start_action(Connected_data *data);
void gtk_set_builder(GtkBuilder *builder);
#endif