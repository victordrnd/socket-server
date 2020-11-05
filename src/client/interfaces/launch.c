#include <gtk/gtk.h>
#include "launch.h"
GtkBuilder *builder = NULL;

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
