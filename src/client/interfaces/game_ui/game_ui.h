/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#ifndef SRC_CLIENT_INTERFACES_GAME_UI_GAME_UI_H_
#define SRC_CLIENT_INTERFACES_GAME_UI_GAME_UI_H_

#include <gtk/gtk.h>

typedef struct _ProgressData {
  GtkProgressBar *progress_bar;
  GSourceFunc callback;
  double progress;
  int time;
} ProgressData;

typedef struct {
  GtkLabel *label;
  char * class;
}BalanceData;

void untoggle_previous_bet_btn(GtkBuilder *builder,GtkWidget *button);
gboolean activate_countdown(ProgressData *data);
gboolean balance_toggle_class(gpointer data);
void toggle_action_button(GtkBuilder *builder, gboolean sensitive);
void toggle_radio_bet_button_sensitive(GtkBuilder *builder, gboolean sensitive);
void stop_count_down(GtkProgressBar *progress_bar);
#endif //SRC_CLIENT_INTERFACES_GAME_UI_GAME_UI_H_