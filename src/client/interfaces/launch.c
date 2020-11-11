#include "launch.h"
#include "../network/communication.h"


void register_styles()
{
    GResource *resource = g_resource_load("output/ressources/app.gressource", NULL);
    g_resources_register(resource);
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(provider, "/org/ics/style.css");
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void init_waiting_room()
{
    GtkBuilder *builder = gtk_builder_new_from_resource("/org/ics/include/glade/waiting_room_interface.glade");
    GtkWidget *waiting_room = GTK_WIDGET(gtk_builder_get_object(builder, "waiting_room_window"));
    gtk_window_set_keep_above(waiting_room, TRUE);
    gtk_widget_show(waiting_room);
}
/**
 * @brief  Init game window
 * 
 * @param argc 
 * @param argv 
 * @param c_game current game
 */
void init_main_window(int argc, char **argv)
{
    GtkWidget *win;
    gtk_init(&argc, &argv);
    register_styles();
    GtkBuilder *builder = gtk_builder_new_from_resource("/org/ics/include/glade/game_interface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));

    gtk_builder_connect_signals(builder, builder);
    gtk_widget_show(win);
    g_signal_connect(G_OBJECT(win), "destroy", close_main_window, NULL);
    //init_waiting_room();
    gtk_main();
}





void close_main_window(gboolean is_cnx_closed)
{
    gtk_main_quit();
    if (is_cnx_closed == FALSE)
        close_connection();
}
