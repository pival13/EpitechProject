/*
** EPITECH PROJECT, 2019
** animation.c
** File description:
** animation main_menu
*/

#include "my.h"

static void animation_button_ig(rpg_t *w, int id)
{
    int speed = 20;

    if ((collision_cursor(w->cursor, w->ingame->buttons[id]) == 1
        && w->key_mode == M_MODE))
        activate_animation(w->ingame->buttons[id], w->clock);
    else if (w->key_mode == K_MODE && w->ingame->key_pos == id
        && w->ingame->key_pos2 == 0)
        activate_animation(w->ingame->buttons[id], w->clock);
    else
        deactivate_animation(w->ingame->buttons[id], w->clock);
    animation_prog_scale(w->ingame->buttons[id], w->clock, 1.3, speed);
}

static void animation_shop_ig(rpg_t *w, int id)
{
    int speed = 20;

    if ((collision_cursor(w->cursor, w->ingame->shop[id]) == 1
        && w->key_mode == M_MODE))
        activate_animation(w->ingame->shop[id], w->clock);
    else if (w->key_mode == K_MODE && w->ingame->key_pos == id
        && w->ingame->key_pos2 == 1)
        activate_animation(w->ingame->shop[id], w->clock);
    else
        deactivate_animation(w->ingame->shop[id], w->clock);
    animation_prog_scale(w->ingame->shop[id], w->clock, 1.3, speed);
}

void animation_buttons_ig(rpg_t *w)
{
    for (int i = 0; i < 5; i++) {
        animation_button_ig(w, i);
        animation_shop_ig(w, i);
    }
}
