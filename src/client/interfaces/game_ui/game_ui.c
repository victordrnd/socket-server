#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "game_ui.h"
#include "../../game/game.h"
GtkWidget *previousToggledBtn = NULL;

/**
 * @brief Stop execution for a delay
 * 
 * @param msecs duration in milliseconds 
 */
void delay(unsigned int msecs)
{
    clock_t goal = msecs * CLOCKS_PER_SEC / 1000 + clock();
    while (goal > clock())
        ;
}

/**
 * @brief Untoggle previously activated button
 * 
 * @param button button to toggle
 */
void untoggle_previous_bet_btn(GtkBuilder *builder, GtkWidget *button)
{
    if (previousToggledBtn == NULL)
    {
        previousToggledBtn = (GtkWidget *)gtk_builder_get_object(builder, "mise_10"); //selected by default
    }
    if (previousToggledBtn != button)
    {
        GtkStyleContext *context = gtk_widget_get_style_context(button);
        gtk_style_context_add_class(context, "selected");

        GtkStyleContext *PreviousButtoncontext = gtk_widget_get_style_context(previousToggledBtn);
        gtk_style_context_remove_class(PreviousButtoncontext, "selected");

        previousToggledBtn = button;
        g_print("%d\n", game_get_current_bet());
    }
}

/**
 * @brief Activate countdown for progress_bar
 * 
 * @param progress_bar GtkWidget (GtkProgressBar)
 * @param seconds time to go to 0
 * @param fps fraps per seconds for animation
 */
void activate_countdown(GtkProgressBar *progress_bar, int seconds, int fps)
{
    gtk_widget_show((GtkWidget *)progress_bar);
    gtk_progress_bar_set_show_text(progress_bar, TRUE);
    for (int i = seconds * fps; i >= 0; i--)
    {
        gdouble fraction = (i * (1.0 / seconds)) / fps;
        if ((i / (fps / 10)) % 10 == 0)
        {
            char *res = (char *)malloc(3 * sizeof(char));
            sprintf(res, "%.f s", (double)i / fps);
            gtk_progress_bar_set_text(progress_bar, res);
            free(res);
        }
        gtk_progress_bar_set_fraction(progress_bar, fraction);
        while (gtk_events_pending())
            gtk_main_iteration();
        delay(1000 / fps);
    }
    gtk_widget_hide((GtkWidget *)progress_bar);
}

void stop_count_down(GtkProgressBar *progress_bar)
{
    gtk_widget_hide((GtkWidget *)progress_bar);
    gtk_progress_bar_set_fraction(progress_bar, (gdouble)1);
}

void toggle_action_button(GtkBuilder *builder, gboolean sensitive)
{
    GtkWidget *betray_btn = (GtkWidget *)gtk_builder_get_object(builder, "betray_btn");
    GtkWidget *collaborate_btn = (GtkWidget *)gtk_builder_get_object(builder, "collaborate_btn");
    gtk_widget_set_sensitive(betray_btn, sensitive);
    gtk_widget_set_sensitive(collaborate_btn, sensitive);
}
