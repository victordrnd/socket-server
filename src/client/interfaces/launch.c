#include <gtk/gtk.h>
#include "launch.h"

#include <stdbool.h>
#include <gtk/gtk.h>

GtkBuilder *builder = NULL;


void on_mise_10_selected(GtkWidget *button)
{
    GtkWidget  *rbtn_label;
    GtkWidget  *rbtn_state;

    rbtn_label = gtk_radio_button_new_with_label (builder, "cb_10");

    printf("%s\n", gtk_button_get_label(&rbtn_label));
}

void on_mise_25_selected()
{
    GtkWidget  *rbtn_label;
    GtkWidget  *rbtn_state;

    rbtn_label = gtk_radio_button_new_with_label (builder, "cb_25");

    printf("%s\n", gtk_button_get_label(&rbtn_label));
}

void on_mise_50_selected()
{
    GtkWidget  *rbtn_label;
    GtkWidget  *rbtn_state;

    rbtn_label = gtk_radio_button_new_with_label (builder, "cb_50");

    printf("%s\n", gtk_button_get_label(&rbtn_label));
}

void on_mise_100_selected()
{
    GtkWidget  *rbtn_label;
    GtkWidget  *rbtn_state;                                              

    rbtn_label = gtk_radio_button_new_with_label (builder, "cb_100");

    printf("%s\n", gtk_button_get_label(&rbtn_label));
}

void btn_collab_toggled_cb()
{
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(builder, "btn_collab"));
    printf("%s", gtk_button_get_label(&btn));
}

void btn_trahir_toggled_cb()
{
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(builder, "btn_trahir"));
    printf("%s", gtk_button_get_label(&btn));
}

void init_main_window(int argc, char **argv){
    GtkWidget *win;
    
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("src/client/ressources/glade/game_interface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}
