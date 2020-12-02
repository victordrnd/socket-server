/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include "handlers.h"
#include "../game_ui/game_ui.h"
#include "../../../common/game.h"
#include "../../game/game.h"
#include "../../network/actions.h"
#include <sys/time.h>

GtkBuilder *builder = NULL;
struct timeval round_start_time;
int timer_id = 0;
/**
 * @brief Mise 10 handler
 * 
 * @param button clicked button
 */
void on_mise_10_selected(GtkButton *button)
{
    game_set_current_bet(10);
    untoggle_previous_bet_btn(builder, (GtkWidget *)button);
}



/**
 * @brief Mise 25 handler
 * 
 * @param button clicked button 
 */
void on_mise_25_selected(GtkButton *button)
{
    game_set_current_bet(25);
    untoggle_previous_bet_btn(builder, (GtkWidget *)button);
}



/**
 * @brief Mise 50 handler
 * 
 * @param button clicked button
 */
void on_mise_50_selected(GtkButton *button)
{
    game_set_current_bet(50);
    untoggle_previous_bet_btn(builder, (GtkWidget *)button);
}



/**
 * @brief Mise 75 handler
 * 
 * @param button clicked button
 */
void on_mise_75_selected(GtkButton *button)
{
    game_set_current_bet(75);
    untoggle_previous_bet_btn(builder, (GtkWidget *)button);
}



/**
 * @brief Mise 100 handler
 * 
 * @param button clicked button
 */
void on_mise_100_selected(GtkButton *button)
{
    game_set_current_bet(100);
    untoggle_previous_bet_btn(builder, (GtkWidget *)button);
}



/**
 * @brief Handler for betray click event
 * 
 * @param button button clicked
 * @param builder Window builder
 */
void on_betray_btn_click(GtkWidget *button __attribute__((unused)))
{
    toggle_action_button(builder, FALSE);
    game_set_action(BETRAY);
    struct timeval action_clicked;
    gettimeofday(&action_clicked, NULL);
    game_set_react_time(round_start_time, action_clicked);
    send_action_packet(get_game());
}



/**
 * @brief Hander for collaborate click event
 * 
 * @param button button clicked
 * @param builder Window builder
 */
void on_collaborate_btn_click(GtkWidget *button __attribute__((unused)))
{
    toggle_action_button(builder, FALSE);
    game_set_action(COLLABORATE);
    struct timeval action_clicked;
    gettimeofday(&action_clicked, NULL);
    game_set_react_time(round_start_time, action_clicked);
    send_action_packet(get_game());
}



/////////////////////
/* NETWORK HANDLERS*/
/////////////////////



/**
 * @brief UI changes on connected action
 * 
 * @param data 
 */
gboolean on_connected_action(Connected_data *data)
{
    GtkLabel *label = (GtkLabel *)gtk_builder_get_object(builder, "balance");
    char amount[10];
    game_set_balance(data->initial_balance);
    sprintf(amount, "$ %d", data->initial_balance);
    gtk_label_set_label(label, amount);
    toggle_action_button(builder, FALSE);
    return FALSE;
}



/**
 * @brief UI changes on failed action
 * 
 */
gboolean on_failed_action(gpointer data __attribute__((unused)))
{
    GtkLabel *label = (GtkLabel *)gtk_builder_get_object(builder, "info_label");
    gtk_label_set_label(label, "Impossible de se connecter au serveur");
    toggle_action_button(builder, FALSE);
    toggle_radio_bet_button_sensitive(builder, FALSE);
    GtkWidget *spinner = (GtkWidget *)gtk_builder_get_object(builder, "spinner_central");
    gtk_widget_hide(spinner);
    GtkStyleContext *context = gtk_widget_get_style_context((GtkWidget *)label);
    gtk_style_context_add_class(context, "error-label");
    return FALSE;
}



/**
 * @brief UI changes on game start action
 * 
 * @param data 
 */
gboolean on_game_start_action(Game_Start_data *data)
{

    GtkWindow *window = (GtkWindow *)gtk_builder_get_object(builder, "app_win");
    game_set_max_rounds(data->max_rounds);
    char title[30];
    sprintf(title, "Round 1 / %d", data->max_rounds);
    gtk_window_set_title(window, title);
    return false;
}

/**
 * @brief Executed on round start progress Bar end
 * 
 */
gboolean on_round_start_ready(gpointer data __attribute__((unused))){
    GtkLabel *label = (GtkLabel *)gtk_builder_get_object(builder, "info_label");
    toggle_action_button(builder, TRUE);
    gtk_label_set_label(label, "A vous de jouer!");
    gettimeofday(&round_start_time, NULL);
    return FALSE;
}

/**
 * @brief UI changes on round start action
 * 
 * @param data 
 */
gboolean on_round_start_action(Round_Start_data *data )
{

    GtkLabel *label = (GtkLabel *)gtk_builder_get_object(builder, "info_label");
    gtk_label_set_label(label, "Le round va bientôt commencer");

    GtkWidget *spinner_central = (GtkWidget *)gtk_builder_get_object(builder, "spinner_central");
    gtk_widget_hide(spinner_central);

    GtkProgressBar *progress_bar = (GtkProgressBar *)gtk_builder_get_object(builder, "progressbar");

    ProgressData *progress_data = (ProgressData *) malloc(sizeof(ProgressData));
    progress_data->progress_bar = progress_bar;
    progress_data->callback = on_round_start_ready;
    progress_data->progress = 1.0;
    progress_data->time = data->waiting_time*2;
    gtk_widget_show((GtkWidget *) progress_bar);
    g_timeout_add(50, activate_countdown, progress_data);
    return FALSE;
}



/**
 * @brief UI changes on round end action
 * 
 * @param data 
 */
gboolean on_round_end_action(Game *data)
{
    GtkWidget *spinner = (GtkWidget *)gtk_builder_get_object(builder, "spinner_central");
    gtk_widget_show(spinner);
    set_game(data);
    game_next_round();
    game_set_balance(data->balance);
    game_set_action(data->action);

    GtkWindow *window = (GtkWindow *)gtk_builder_get_object(builder, "app_win");
    char title[50];
    sprintf(title, "Round %d / %d", data->current_round, data->total_rounds);
    gtk_window_set_title(window, title);

    GtkLabel *label = (GtkLabel *)gtk_builder_get_object(builder, "balance");
    char amount[10];
    sprintf(amount, "$ %d", data->balance);
    gtk_label_set_label(label, amount);
    return FALSE;
}



/**
 * @brief UI changes on game end action
 * 
 * @param data 
 */
gboolean on_game_end_action(Game_End_data *data)
{
    GtkLabel *label = (GtkLabel *)gtk_builder_get_object(builder, "info_label");
    GtkImage *image = (GtkImage *)gtk_builder_get_object(builder, "result_image");
    GtkWidget *spinner = (GtkWidget *)gtk_builder_get_object(builder, "spinner_central");
    gtk_widget_hide(spinner);
    switch (data->result)
    {
    case VICTORY:
    {
        gtk_label_set_label(label, "VICTOIRE !");
        break;
    }
    case DEFEAT:
    {
        gtk_label_set_label(label, "DEFAITE !");
        gtk_image_set_from_resource(image, "/org/ics/include/images/defeat.png");
        break;
    }
    case EQUALITY:
    {
        gtk_label_set_label(label, "EGALITE !");
        gtk_image_set_from_resource(image, "/org/ics/include/images/equality.png");
        break;
    }
    default:
        break;
    }
    gtk_widget_show((GtkWidget *)image);
    return FALSE;
}



/**
 * @brief Set builder
 * 
 * @param buildr 
 */
void gtk_set_builder(GtkBuilder *buildr)
{
    builder = buildr;
}
