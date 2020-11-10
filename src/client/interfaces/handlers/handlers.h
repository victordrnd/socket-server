#ifndef HANDLERS_H
#define HANDLERS_H

#include <gtk/gtk.h>

//Boutons radios
void on_mise_10_selected(GtkToggleButton *button, GtkBuilder *builder);
void on_mise_25_selected(GtkToggleButton *button, GtkBuilder *builder);
void on_mise_50_selected(GtkToggleButton *button, GtkBuilder *builder);
void on_mise_100_selected(GtkToggleButton *button, GtkBuilder *builder);

void on_betray_btn_click(GtkWidget *button, GtkBuilder *builder);
#endif