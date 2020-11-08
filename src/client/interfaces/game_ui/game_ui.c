#include <assert.h>
#include "game_ui.h"

GtkToggleButton *previousToggledBtn;

/**
 * @brief Untoggle previously activated button
 * 
 * @param button 
 */
void untoggle_previous_bet_btn(GtkToggleButton *button)
{
    if (previousToggledBtn != NULL)
    {
        gtk_toggle_button_set_active(previousToggledBtn, FALSE);
        assert(gtk_toggle_button_get_active(previousToggledBtn) == FALSE);
    }
    previousToggledBtn = button;
}