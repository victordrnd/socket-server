#include "handlers.h"
#include "../game_ui/game_ui.h"
#include "../../../common/game.h"
#include "../../game/game.h"

/**
 * @brief Mise 10 handler
 * 
 * @param button clicked button
 */
void on_mise_10_selected(GtkToggleButton *button, GtkBuilder *builder)
{
    game_set_current_bet(10);
    untoggle_previous_bet_btn(builder, button);
}

/**
 * @brief Mise 25 handler
 * 
 * @param button clicked button 
 */
void on_mise_25_selected(GtkToggleButton *button, GtkBuilder *builder)
{
    game_set_current_bet(25);
    untoggle_previous_bet_btn(builder, button);
}

/**
 * @brief Mise 50 handler
 * 
 * @param button clicked button
 */
void on_mise_50_selected(GtkToggleButton *button, GtkBuilder *builder)
{
    game_set_current_bet(50);
    untoggle_previous_bet_btn(builder, button);
}

/**
 * @brief Mise 75 handler
 * 
 * @param button clicked button
 */
void on_mise_75_selected(GtkToggleButton *button, GtkBuilder *builder)
{
    game_set_current_bet(75);
    untoggle_previous_bet_btn(builder, button);
}

/**
 * @brief Mise 100 handler
 * 
 * @param button clicked button
 */
void on_mise_100_selected(GtkToggleButton *button, GtkBuilder *builder)
{
    game_set_current_bet(100);
    untoggle_previous_bet_btn(builder, button);
}

/**
 * @brief 
 * 
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
 * @brief 
 * 
 */
void on_collaborate_btn_click(GtkWidget *button, GtkBuilder *builder)
{
    toggle_action_button(builder, FALSE);
    game_set_action(COLLABORATE);
    GtkProgressBar *progressbar = (GtkProgressBar *) gtk_builder_get_object(builder, "progressbar");
    activate_countdown(progressbar, 20, 20);
    toggle_action_button(builder, TRUE);
}