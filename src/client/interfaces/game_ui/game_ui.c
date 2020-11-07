#include "game_ui.h"

GtkToggleButton *previousToggledBtn;
void untoggle_previous_bet_btn(GtkToggleButton *button)
{
    if (previousToggledBtn != NULL)
    {
        gtk_toggle_button_set_active(previousToggledBtn, FALSE);
    }
    previousToggledBtn = button;
}