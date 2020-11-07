#include <gtk/gtk.h>
#include <stdbool.h>

#include "../utils/config.h"

#include "launch.h"
#include "../game/game.h"
#include "game_ui/game_ui.h"

GtkBuilder *builder = NULL;

void on_mise_10_selected(GtkToggleButton *button)
{
    game_set_current_bet(10);
    untoggle_previous_bet_btn(button);
}

void on_mise_25_selected(GtkToggleButton *button)
{
    untoggle_previous_bet_btn(button);
}

void on_mise_50_selected(GtkToggleButton *button)
{

    untoggle_previous_bet_btn(button);
}

void on_mise_75_selected(GtkToggleButton *button)
{

    untoggle_previous_bet_btn(button);
}

void on_mise_100_selected(GtkToggleButton *button)
{
    untoggle_previous_bet_btn(button);
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

void init_main_window(int argc, char **argv, Game *c_game)
{
    GtkWidget *win;
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("src/client/ressources/glade/game_interface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}
