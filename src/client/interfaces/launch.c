#include "launch.h"


/**
 * @brief  Init game window
 * 
 * @param argc 
 * @param argv 
 * @param c_game current game
 */
void init_main_window(int argc, char **argv)
{
    GtkWidget *win; //, *win1;
    gtk_init(&argc, &argv);
    GResource *resource = g_resource_load("output/ressources/app.gressource", NULL);
    g_resources_register(resource);
    GtkBuilder *builder = gtk_builder_new_from_resource("/org/ics/include/glade/game_interface.glade");
    GtkBuilder *builder1 = gtk_builder_new_from_file("include/glade/waiting_room_interface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(provider, "/org/ics/style.css");
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    //win1 = GTK_WIDGET(gtk_builder_get_object(builder1, "waiting_room_window"));
    gtk_builder_connect_signals(builder, builder);
    //GtkWidget *test = gtk_builder_get_object(builder1, "app_frame");
    //gtk_container_remove(win1, test);
    //gtk_container_remove(win, gtk_builder_get_object(builder, "app_frame"));
    //gtk_container_add(win, test);
    // gtk_window_set_attached_to(win, win1);
    // gtk_window_set_transient_for(win1, win);
    gtk_widget_show(win);
    // gtk_widget_show(win1);
    // TODO on window destroy exit other threads 

    /*
     g_signal_connect(G_OBJECT(win),
        "destroy", gtk_main_quit, NULL);
    */
    gtk_main();
}
