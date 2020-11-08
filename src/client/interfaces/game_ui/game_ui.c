#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "game_ui.h"

GtkToggleButton *previousToggledBtn = NULL;

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
void untoggle_previous_bet_btn(GtkBuilder *builder, GtkToggleButton *button)
{
    if (previousToggledBtn == NULL)
    {
        previousToggledBtn = gtk_builder_get_object(builder, "mise_10"); //selected by default
    }
    gtk_toggle_button_set_active(previousToggledBtn, FALSE);
    assert(gtk_toggle_button_get_active(previousToggledBtn) == FALSE);
    previousToggledBtn = button;
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
    gtk_widget_show(progress_bar);
    gtk_progress_bar_set_show_text(progress_bar, TRUE);
    for (int i = seconds * fps; i >= 0; i--)
    {
        gdouble fraction = (i * (1.0 / seconds)) / fps;
        if ((i / (fps / 10)) % 10 == 0)
        {
            char *res = malloc(3 * sizeof(char));
            sprintf(res, "%.f s", (double)i / fps);
            gtk_progress_bar_set_text(progress_bar, res);
            free(res);
        }
        gtk_progress_bar_set_fraction(progress_bar, fraction);
        while (gtk_events_pending())
            gtk_main_iteration();
        delay(1000 / fps);
    }
    gtk_widget_hide(progress_bar);
}