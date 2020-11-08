#include <gtk/gtk.h>
#include <stdbool.h>

#include "../utils/config.h"

#include "launch.h"
#include "../game/game.h"
#include "game_ui/game_ui.h"


/**
 * @brief Mise 10 handler
 * 
 * @param button clicked button
 */
void on_mise_10_selected(GtkToggleButton *button, GtkBuilder *builder)
{
    game_set_current_bet(10);
    untoggle_previous_bet_btn(builder,button);
}

/**
 * @brief Mise 25 handler
 * 
 * @param button clicked button 
 */
void on_mise_25_selected(GtkToggleButton *button, GtkBuilder *builder)
{
    untoggle_previous_bet_btn(builder,button);
}

/**
 * @brief Mise 50 handler
 * 
 * @param button clicked button
 */
void on_mise_50_selected(GtkToggleButton *button, GtkBuilder *builder)
{

    untoggle_previous_bet_btn(builder,button);
}

/**
 * @brief Mise 75 handler
 * 
 * @param button clicked button
 */
void on_mise_75_selected(GtkToggleButton *button, GtkBuilder *builder)
{

    untoggle_previous_bet_btn(builder,button);
}

/**
 * @brief Mise 100 handler
 * 
 * @param button clicked button
 */
void on_mise_100_selected(GtkToggleButton *button, GtkBuilder *builder)
{
    untoggle_previous_bet_btn(builder, button);
}

/**
 * @brief 
 * 
 */
void on_betray_btn_click(GtkButton *button, GtkProgressBar *progressbar){
    // toggle_action_sensitivity(button )
    gtk_widget_set_sensitive (button, FALSE);
    activate_countdown(progressbar, 10, 20);
    gtk_widget_set_sensitive (button, TRUE);
}

/**
 * @brief 
 * 
 */
void on_collaborate_btn_click()
{

}

/**
 * @brief  Init game window
 * 
 * @param argc 
 * @param argv 
 * @param c_game current game
 */
void init_main_window(int argc, char **argv, Game *c_game)
{
    GtkWidget *win, *win1;
    gtk_init(&argc, &argv);
    GResource *resource = g_resource_load ("output/ressources/app.gressource",NULL);
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

    gtk_main();
}
