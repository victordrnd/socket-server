#include <gtk/gtk.h>
#include "../game/game.h"

#ifndef LAUNCH_HEADER_H
#define LAUNCH_HEADER_H

typedef struct 
{
    // bool rb_state;
    char rb_label;

} radio_button;

typedef struct
{
    

} toggle_button;

//Boutons radios
void on_mise_10_selected(GtkToggleButton *button);
void on_mise_25_selected(GtkToggleButton *button);
void on_mise_50_selected(GtkToggleButton *button);
void on_mise_100_selected(GtkToggleButton *button);

//Boutons toggleds
void btn_collab_toggled_cb();
void btn_trahir_toggled_cb();

//Plateau du jeu
void init_main_window(int argc, char **argv, Game *c_game);

//Glade builder
GtkBuilder *get_gtk_builder();

#endif