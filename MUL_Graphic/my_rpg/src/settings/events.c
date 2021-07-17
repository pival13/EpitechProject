/*
** EPITECH PROJECT, 2019
** events.c
** File description:
** events settings
*/

#include "my.h"

void animation_background_sett(rpg_t *w)
{
    get_time(w->mm->bgd->time_move, w->clock);
    obj_move(w->mm->bgd, 150 * w->mm->bgd->time_move->seconds, 0);
    if (w->mm->bgd->pos.x >= 1920)
        obj_set_position(w->mm->bgd, 0, 0);
    reset_time(w->mm->bgd->time_move, w->clock);
}

void animation_button_sett(rpg_t *w)
{
    int speed = 20;

    if (collision_cursor(w->cursor, w->sett->return_button) == 1 ||
        w->sett->key_pos == 2)
        activate_animation(w->sett->return_button, w->clock);
    else
        deactivate_animation(w->sett->return_button, w->clock);
    animation_prog_scale(w->sett->return_button, w->clock, 1.3, speed);
}

void set_click_volumes(rpg_t *w)
{
    for (int i = 0; i < 10; i++) {
        if (click_button(w->cursor, w->sett->sound_bar[i], w->event) == 1)
            w->sett->sound_volume = (i + 1) * 10;
        if (click_button(w->cursor, w->sett->music_bar[i], w->event) == 1)
            w->sett->music_volume = (i + 1) * 10;
    }
    if (click_button(w->cursor, w->sett->sound_icon, w->event) == 1)
        w->sett->sound_volume = 0;
    if (click_button(w->cursor, w->sett->music_icon, w->event) == 1)
        w->sett->music_volume = 0;
}

void change_sprites_sm_volume(rpg_t *w)
{
    int s_vol = w->sett->sound_volume / 10;
    int m_vol = w->sett->music_volume / 10;

    (s_vol > 0) ? (set_anim_sprite(w->sett->sound_icon, 0, 0)) :
    (set_anim_sprite(w->sett->sound_icon, 0, 1));
    (m_vol > 0) ? (set_anim_sprite(w->sett->music_icon, 0, 0)) :
    (set_anim_sprite(w->sett->music_icon, 0, 1));
    for (int i = 0; i < 10; i++) {
        (s_vol > 0) ? (set_anim_sprite(w->sett->sound_bar[i], 0, 1)) :
        (set_anim_sprite(w->sett->sound_bar[i], 0, 0));
        (m_vol > 0) ? (set_anim_sprite(w->sett->music_bar[i], 0, 1)) :
        (set_anim_sprite(w->sett->music_bar[i], 0, 0));
        s_vol--;
        m_vol--;
    }
}

void events_settings(rpg_t *w)
{
    animation_background_sett(w);
    animation_button_sett(w);
    if (click_button(w->cursor, w->sett->return_button, w->event) == 1 ||
        (w->sett->key_pos == 2 && KEY_I()))
        change_page_back(w);
    key_cursor_settings(w);
    set_click_volumes(w);
    change_sprites_sm_volume(w);
    set_volume(w);
}
