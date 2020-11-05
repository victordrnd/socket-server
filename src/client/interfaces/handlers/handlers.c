#include <stdbool.h>
#include <gtk/gtk.h>

#include "../launch.h"
#include "handlers.h"

void on_mise_10_selected(GtkWidget *button)
{
    bool *rb_state;
    char *rb_label;


    rb_label = gtk_button_get_label(GTK_BUTTON(button));

    g_print("%s est %s\n", rb_label);
}

void on_mise_25_selected()
{
}

void on_mise_50_selected()
{
}

void on_mise_100_selected()
{
}



void btn_collab_toggled_cb()
{
}