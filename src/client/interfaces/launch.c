#include "launch.h"

builder = NULL;
void init_main_window(int argc, char **argv){
    GtkWidget *win;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("src/client/ressources/glade/interface_prisonnier.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}