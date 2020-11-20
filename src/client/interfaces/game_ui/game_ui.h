
#ifndef GAME_UI_HEADER_H
#define GAME_UI_HEADER_H

#include <gtk/gtk.h>

void untoggle_previous_bet_btn(GtkBuilder *builder,GtkWidget *button);
void activate_countdown(GtkProgressBar *progress_bar, int seconds, int fps);
void toggle_action_button(GtkBuilder *builder, gboolean sensitive);
void radio_bet_button(GtkBuilder *builder, gboolean sensitive);
void stop_count_down(GtkProgressBar *progress_bar);
#endif