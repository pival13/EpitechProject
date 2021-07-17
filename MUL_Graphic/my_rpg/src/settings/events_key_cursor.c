/*
** EPITECH PROJECT, 2019
** events_key_cursor.c
** File description:
** events_key_cursor
*/

#include "my.h"

void animation_key_cursor_settings(rpg_t *w)
{
    int speed = 20;

    if (w->sett->key_pos == 0) {
        activate_animation(w->sett->sound_icon, w->clock);
    } else {
        deactivate_animation(w->sett->sound_icon, w->clock);
    }
    if (w->sett->key_pos == 1) {
        activate_animation(w->sett->music_icon, w->clock);
    } else {
        deactivate_animation(w->sett->music_icon, w->clock);
    }
    animation_prog_scale(w->sett->music_icon, w->clock, 1.3, speed);
    animation_prog_scale(w->sett->sound_icon, w->clock, 1.3, speed);
}

void key_cursor_settings_interactions(rpg_t *w)
{
    (w->sett->key_pos == 0 && KEY_Q() && w->sett->sound_volume > 0)
    ? (w->sett->sound_volume -= 10) : (0);
    (w->sett->key_pos == 1 && KEY_Q() && w->sett->music_volume > 0)
    ? (w->sett->music_volume -= 10) : (0);
    (w->sett->key_pos == 0 && KEY_D() && w->sett->sound_volume < 100)
    ? (w->sett->sound_volume += 10) : (0);
    (w->sett->key_pos == 1 && KEY_D() && w->sett->music_volume < 100)
    ? (w->sett->music_volume += 10) : (0);
    (w->sett->key_pos == 0 && KEY_I())
    ? (w->sett->sound_volume = 0) : (0);
    (w->sett->key_pos == 1 && KEY_I())
    ? (w->sett->music_volume = 0) : (0);
    animation_key_cursor_settings(w);
}

void key_cursor_settings(rpg_t *w)
{
    (KEY_Z()) ? (w->sett->key_pos += 1) : (0);
    (KEY_S()) ? (w->sett->key_pos -= 1) : (0);
    (w->sett->key_pos < 0) ? (w->sett->key_pos = 2) : (0);
    (w->sett->key_pos > 2) ? (w->sett->key_pos = 0) : (0);
    if (w->key_mode == K_MODE)
        key_cursor_settings_interactions(w);
}
