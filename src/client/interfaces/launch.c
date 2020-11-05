#include "launch.h"

#include <stdbool.h>
#include <gtk/gtk.h>

GtkBuilder *builder = NULL;


void on_mise_10_selected(GtkWidget *button)
{
    GtkWidget  *rbtn_label;

    rbtn_label = gtk_radio_button_new_with_label (builder, "mise de 10");

    printf("%s\n", gtk_button_get_label(&rbtn_label));
}

void on_mise_25_selected()
{
    GtkWidget  *rbtn_label;

    rbtn_label = gtk_radio_button_new_with_label (builder, "mise de 25");

    printf("%s\n", gtk_button_get_label(&rbtn_label));
}

void on_mise_50_selected()
{
    GtkWidget  *rbtn_label;

    rbtn_label = gtk_radio_button_new_with_label (builder, "mise de 50");

    printf("%s\n", gtk_button_get_label(&rbtn_label));
}

void on_mise_100_selected()
{
    GtkWidget  *rbtn_label;

    rbtn_label = gtk_radio_button_new_with_label (builder, "mise de 100");

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
    builder = gtk_builder_new_from_file("src/client/ressources/glade/interface_prisonnier.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}

GtkBuilder *get_gtk_builder(){
    return builder;
}