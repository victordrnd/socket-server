#include "handlers.h"
#include "../game_ui/game_ui.h"
#include "../../../common/game.h"
#include "../../game/game.h"

GtkBuilder *builder = NULL;
/**
 * @brief Mise 10 handler
 * 
 * @param button clicked button
 */
void on_mise_10_selected(GtkButton *button, GtkBuilder *builder)
{
    game_set_current_bet(10);
    untoggle_previous_bet_btn(builder, (GtkWidget *) button);
}

/**
 * @brief Mise 25 handler
 * 
 * @param button clicked button 
 */
void on_mise_25_selected(GtkButton *button, GtkBuilder *builder)
{
    game_set_current_bet(25);
    untoggle_previous_bet_btn(builder, (GtkWidget *) button);
}

/**
 * @brief Mise 50 handler
 * 
 * @param button clicked button
 */
void on_mise_50_selected(GtkButton *button, GtkBuilder *builder)
{
    game_set_current_bet(50);
    untoggle_previous_bet_btn(builder, (GtkWidget *) button);
}

/**
 * @brief Mise 75 handler
 * 
 * @param button clicked button
 */
void on_mise_75_selected(GtkButton *button, GtkBuilder *builder)
{
    game_set_current_bet(75);
    untoggle_previous_bet_btn(builder, (GtkWidget *) button);
}

/**
 * @brief Mise 100 handler
 * 
 * @param button clicked button
 */
void on_mise_100_selected(GtkButton *button, GtkBuilder *builder)
{
    game_set_current_bet(100);
    untoggle_previous_bet_btn(builder, (GtkWidget *) button);
}

/**
 * @brief Handler for betray click event
 * 
 * @param button button clicked
 * @param builder Window builder
 */
void on_betray_btn_click(GtkWidget *button, GtkBuilder *builder)
{
    toggle_action_button(builder, FALSE);
    game_set_action(BETRAY);
    GtkProgressBar *progressbar = (GtkProgressBar *) gtk_builder_get_object(builder, "progressbar");
    activate_countdown(progressbar, 20, 20);
    toggle_action_button(builder, TRUE);
}

/**
 * @brief Hander for collaborate click event
 * 
 * @param button button clicked
 * @param builder Window builder
 */
void on_collaborate_btn_click(GtkWidget *button, GtkBuilder *builder)
{
    toggle_action_button(builder, FALSE);
    game_set_action(COLLABORATE);
    GtkProgressBar *progressbar = (GtkProgressBar *) gtk_builder_get_object(builder, "progressbar");
    activate_countdown(progressbar, 20, 20);
    toggle_action_button(builder, TRUE);
}


void on_connected_action(Connected_data *data){
    GtkLabel *label = (GtkLabel *) gtk_builder_get_object(builder, "balance");
    char amount[10];
    sprintf(amount, "$ %d", data->initial_balance);
    gtk_label_set_label(label, amount);
}   

void on_game_start_action(Game_Start_data *data){

    GtkWindow *window = (GtkLabel *) gtk_builder_get_object(builder, "app_win");
    game_set_max_rounds(data->max_rounds);
    char title[50];
    sprintf(title, "Round 1 / %d", data->max_rounds);
    gtk_window_set_title (window, title);
}

void on_round_start_action(Connected_data *data){
    GtkProgressBar *progress_bar = (GtkProgressBar *) gtk_builder_get_object(builder, "progressbar");
    activate_countdown(progress_bar, 10,20);
    GtkLabel *label = (GtkLabel *) gtk_builder_get_object(builder, "info_label");
    gtk_label_set_label(label,"La partie va bientôt commencer");
}

void gtk_set_builder(GtkBuilder *buildr){
    builder = buildr;
}

