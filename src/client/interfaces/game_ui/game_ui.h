/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#ifndef SRC_CLIENT_INTERFACES_GAME_UI_GAME_UI_H_
#define SRC_CLIENT_INTERFACES_GAME_UI_GAME_UI_H_

#include <gtk/gtk.h>

void untoggle_previous_bet_btn(GtkBuilder *builder,GtkWidget *button);
void activate_countdown(GtkProgressBar *progress_bar, int seconds, int fps);
void toggle_action_button(GtkBuilder *builder, gboolean sensitive);
void toggle_radio_bet_button_sensitive(GtkBuilder *builder, gboolean sensitive);
void stop_count_down(GtkProgressBar *progress_bar);
#endif //SRC_CLIENT_INTERFACES_GAME_UI_GAME_UI_H_