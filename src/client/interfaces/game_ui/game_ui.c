/*
 * Created on Sun Nov 22 2020
 *
 * Copyright (c) 2020 Victor Durand & Raphael Rabechault & Tom Mollon & Lisa Seigle-Morier
 */

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "game_ui.h"
#include "../../game/game.h"
GtkWidget *previousToggledBtn = NULL;

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
        GtkStyleContext *context = gtk_widget_get_style_context((GtkWidget *)button);
        gtk_style_context_add_class(context, "selected");

        GtkStyleContext *PreviousButtoncontext = gtk_widget_get_style_context((GtkWidget *)previousToggledBtn);
        gtk_style_context_remove_class(PreviousButtoncontext, "selected");

        previousToggledBtn = button;
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
        if (((int)fraction*100) % 10 == 0)
        {
            char *res = (char *)malloc(3 * sizeof(char));
            sprintf(res, "%.f s", (double)i / fps);
            gtk_progress_bar_set_text(progress_bar, res);
            free(res);
        }
        gtk_progress_bar_set_fraction(progress_bar, fraction);
        while (gtk_events_pending())
            gtk_main_iteration();
        g_usleep(1e6 / fps);
    }
    gtk_widget_hide((GtkWidget *)progress_bar);
}



/**
 * @brief Hide countdown progress bar
 * 
 * @param progress_bar progressbar to hide
 */
void stop_count_down(GtkProgressBar *progress_bar)
{
    gtk_widget_hide((GtkWidget *)progress_bar);
    gtk_progress_bar_set_fraction(progress_bar, (gdouble)1);
}



/**
 * @brief Activate or desactivate action buttons
 * 
 * @param builder Window Builder
 * @param sensitive TRUE to toggle sensitiveness
 */
void toggle_action_button(GtkBuilder *builder, gboolean sensitive)
{
    GtkWidget *betray_btn = (GtkWidget *)gtk_builder_get_object(builder, "betray_btn");
    GtkWidget *collaborate_btn = (GtkWidget *)gtk_builder_get_object(builder, "collaborate_btn");
    gtk_widget_set_sensitive(betray_btn, sensitive);
    gtk_widget_set_sensitive(collaborate_btn, sensitive);
}



/**
 * @brief Toogle radio bet buttons sensitivity
 * 
 * @param builder 
 * @param sensitive 
 */
void toggle_radio_bet_button_sensitive(GtkBuilder *builder, gboolean sensitive)
{

    GtkWidget *mise_10 = (GtkWidget *)gtk_builder_get_object(builder, "mise_10");
    GtkWidget *mise_25 = (GtkWidget *)gtk_builder_get_object(builder, "mise_25");
    GtkWidget *mise_50 = (GtkWidget *)gtk_builder_get_object(builder, "mise_50");
    GtkWidget *mise_75 = (GtkWidget *)gtk_builder_get_object(builder, "mise_75");
    GtkWidget *mise_100 = (GtkWidget *)gtk_builder_get_object(builder, "mise_100");
    gtk_widget_set_sensitive(mise_10, sensitive);
    gtk_widget_set_sensitive(mise_25, sensitive);
    gtk_widget_set_sensitive(mise_50, sensitive);
    gtk_widget_set_sensitive(mise_75, sensitive);
    gtk_widget_set_sensitive(mise_100, sensitive);
}