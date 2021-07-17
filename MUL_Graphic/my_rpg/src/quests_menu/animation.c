/*
** EPITECH PROJECT, 2019
** animation.c
** File description:
** animation main_menu
*/

#include "my.h"

void animation_button_qm2(rpg_t *w, int speed)
{
    if ((collision_cursor(w->cursor, w->qm->return_button) == 1 &&
        w->key_mode == M_MODE) ||
        (0 == w->qm->key_pos && w->key_mode == K_MODE)) {
        activate_animation(w->qm->switch_name_buttons[0], w->clock);
        activate_animation(w->qm->switch_name_buttons[1], w->clock);
    } else {
        deactivate_animation(w->qm->switch_name_buttons[0], w->clock);
        deactivate_animation(w->qm->switch_name_buttons[1], w->clock);
    }
    animation_prog_scale(w->qm->switch_name_buttons[0], w->clock, 1.5, speed);
    animation_prog_scale(w->qm->switch_name_buttons[1], w->clock, 1.5, speed);
}

void animation_button_qm(rpg_t *w)
{
    int speed = 20;

    if ((collision_cursor(w->cursor, w->qm->return_button) == 1 &&
        w->key_mode == M_MODE) ||
        (1 == w->qm->key_pos && w->key_mode == K_MODE))
        activate_animation(w->qm->return_button, w->clock);
    else
        deactivate_animation(w->qm->return_button, w->clock);
    animation_prog_scale(w->qm->return_button, w->clock, 1.3, speed);
    animation_button_qm2(w, speed);
}

void animation_buttons_qm(rpg_t *w)
{
    animation_button_qm(w);
}
