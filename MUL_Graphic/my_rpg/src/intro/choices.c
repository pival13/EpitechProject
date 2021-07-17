/*
** EPITECH PROJECT, 2019
** choices.c
** File description:
** choices events
*/

#include "my.h"

void set_pos_key_cursor_intro(rpg_t *w)
{
    sfVector2f pos1 = {SIZE(x) * 0.49, SIZE(y) / 3 - 200};
    sfVector2f pos2 = {SIZE(x) * 0.49, SIZE(y) / 3 };
    sfVector2f pos3 = {SIZE(x) * 0.49, SIZE(y) / 3 + 200};

    if (w->intro->key_pos == 0)
        sfSprite_setPosition(w->intro->key_cursor->sprite, pos1);
    if (w->intro->key_pos == 1)
        sfSprite_setPosition(w->intro->key_cursor->sprite, pos2);
    if (w->intro->key_pos == 2)
        sfSprite_setPosition(w->intro->key_cursor->sprite, pos3);
    for (int i = 0; i < 3; i++) {
        if (w->intro->key_pos == i && w->key_mode == K_MODE)
            edit_text_color(w->intro->choices[i], 255, 10, 10);
        else
            edit_text_color(w->intro->choices[i], 29, 23, 20);
    }
}

void events_choices_intro_expanded(rpg_t *w)
{
    for (int i = 0; i < 3; i++) {
        if (collision_cursor_text(w->cursor, w->intro->choices[i])
            && w->key_mode == M_MODE)
            edit_text_color(w->intro->choices[i], 255, 10, 10);
        else
            edit_text_color(w->intro->choices[i], 29, 23, 20);
    }
    if (w->key_mode == K_MODE)
        set_visible(w->intro->key_cursor->sprite);
    else
        set_invisible(w->intro->key_cursor->sprite);
    (KEY_Z()) ? (w->intro->key_pos -= 1) : (0);
    (KEY_S()) ? (w->intro->key_pos += 1) : (0);
    (w->intro->key_pos > 2) ? (w->intro->key_pos = 0) : (0);
    (w->intro->key_pos < 0) ? (w->intro->key_pos = 2) : (0);
    (w->key_mode == K_MODE) ? (set_pos_key_cursor_intro(w)) : (0);
}
