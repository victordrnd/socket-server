#ifndef HANDLERS_H
#define HANDLERS_H

#include <gtk/gtk.h>

//Boutons radios
void on_mise_10_selected(GtkButton *button, GtkBuilder *builder);
void on_mise_25_selected(GtkButton *button, GtkBuilder *builder);
void on_mise_50_selected(GtkButton *button, GtkBuilder *builder);
void on_mise_100_selected(GtkButton *button, GtkBuilder *builder);

void on_betray_btn_click(GtkWidget *button, GtkBuilder *builder);
#endif