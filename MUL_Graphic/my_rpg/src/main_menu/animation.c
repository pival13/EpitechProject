/*
** EPITECH PROJECT, 2019
** animation.c
** File description:
** animation main_menu
*/

#include "my.h"

void animation_button_mm(rpg_t *w, int id)
{
    int speed = 20;
    int id_n = id;

    (id_n > 2) ? (id_n -= 3) : (0);
    if ((w->mm->play_mode == 0 && id < 3) ||
        (w->mm->play_mode == 1 && id >= 3)) {
        set_visible(w->mm->buttons[id]->sprite);
    } else {
        set_invisible(w->mm->buttons[id]->sprite);
    }
    if ((collision_cursor(w->cursor, w->mm->buttons[id]) == 1 &&
        w->key_mode == M_MODE) ||
        (id_n == w->mm->key_pos && w->key_mode == K_MODE))
        activate_animation(w->mm->buttons[id], w->clock);
    else
        deactivate_animation(w->mm->buttons[id], w->clock);
    animation_prog_scale(w->mm->buttons[id], w->clock, 1.3, speed);
}

void animation_background_mm(rpg_t *w)
{
    get_time(w->mm->bgd->time_move, w->clock);
    obj_move(w->mm->bgd, 150 * w->mm->bgd->time_move->seconds, 0);
    if (w->mm->bgd->pos.x >= 1920)
        obj_set_position(w->mm->bgd, 0, 0);
    reset_time(w->mm->bgd->time_move, w->clock);
}

void animation_title_mm(rpg_t *w)
{
    float delay = 0.2;

    get_time(w->mm->title->time_move, w->clock);
    if (w->mm->title->time_move->seconds > delay) {
        anim_sprite(w->mm->title, 0, 1);
        reset_time(w->mm->title->time_move, w->clock);
    }
}

void animation_buttons_mm(rpg_t *w)
{
    for (int i = 0; i < 7; i++) {
        animation_button_mm(w, i);
    }
    animation_title_mm(w);
    animation_background_mm(w);
}
