/*
** EPITECH PROJECT, 2019
** events.c
** File description:
** events qm
*/

#include "my.h"

int buttons_events_qm2(rpg_t *w)
{
    if (click_button(w->cursor, w->qm->switch_name_buttons[1], w->event)) {
        change_title_qm_right(w);
        return (0);
    }
    if (click_button(w->cursor, w->qm->switch_name_buttons[0], w->event)) {
        change_title_qm_left(w);
        return (0);
    }
    return (0);
}

int buttons_events_qm(rpg_t *w)
{
    if (click_button(w->cursor, w->qm->return_button, w->event)) {
        change_page_back(w);
        return (0);
    }
    buttons_events_qm2(w);
    return (0);
}

void events_quests_menu(rpg_t *w)
{
    static int i = 0;

    if (i == 0) {
        load_qm(w);
        i = 1;
    }
    buttons_events_qm(w);
    animation_buttons_qm(w);
    key_cursor_qm(w);
}
