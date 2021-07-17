/*
** EPITECH PROJECT, 2019
** ingame menue
** File description:
** display ingame menue
*/

#include "my.h"

void events_ig_key_mode_buttons(rpg_t *w, int *i)
{
    get_time(w->ingame->buttons[SAVE_IG]->time_move, w->clock);
    if (w->ingame->key_pos == SAVE_IG && KEY_I() && w->ingame->key_pos2 == 0) {
        save_save(w);
        reset_time(w->ingame->buttons[SAVE_IG]->time_move, w->clock);
    }
    if (w->ingame->key_pos == QUIT_IG && KEY_I() && w->ingame->key_pos2 == 0) {
        change_page(w, MENU);
        *i = 0;
    }
    if (w->ingame->key_pos == SETTINGS_IG && KEY_I() &&
        w->ingame->key_pos2 == 0)
        change_page(w, SETT);
    if (w->ingame->key_pos == INVENTORY && KEY_I() &&
        w->ingame->key_pos2 == 0) {
        change_page(w, CH);
    }
    if (w->ingame->key_pos == QUEST && KEY_I() && w->ingame->key_pos2 == 0)
        change_page(w, QM);
}

void events_ig_key_mode(rpg_t *w, int *i)
{
    (KEY_Z()) ? (w->ingame->key_pos -= 1) : (0);
    (KEY_S()) ? (w->ingame->key_pos += 1) : (0);
    (KEY_Q()) ? (w->ingame->key_pos2 -= 1) : (0);
    (KEY_D()) ? (w->ingame->key_pos2 += 1) : (0);
    (w->ingame->key_pos2 > 1) ? (w->ingame->key_pos2 = 0) : (0);
    (w->ingame->key_pos2 < 0) ? (w->ingame->key_pos2 = 1) : (0);
    (w->ingame->key_pos > 4) ? (w->ingame->key_pos = 0) : (0);
    (w->ingame->key_pos < 0) ? (w->ingame->key_pos = 4) : (0);
    events_ig_key_mode_buttons(w, i);
}

void ingame_menu(rpg_t *w, int *i)
{
    animation_buttons_ig(w);
    if (w->key_mode == M_MODE)
        event_ingame_menu(w, i);
    else
        events_ig_key_mode(w, i);
    shop_events(w);
    sfRenderWindow_drawSprite(w->win, w->ingame->bgd->sprite, NULL);
    get_time(w->ingame->no_money->time_anim, w->clock);
    get_time(w->ingame->bought->time_anim, w->clock);
    for (int a = 0; a != 5; a++) {
        sfRenderWindow_drawSprite(w->win, w->ingame->buttons[a]->sprite, NULL);
        sfRenderWindow_drawSprite(w->win, w->ingame->shop[a]->sprite, NULL);
    }
    (w->ingame->buttons[SAVE_IG]->time_move->seconds <= 0.8)
    ? (draw_sprite(w->win, w->ingame->message_save->sprite)) : (0);
    if (w->ingame->bought->time_anim->seconds <= 0.8) {
        draw_sprite(w->win, w->ingame->bought->sprite);
    } if (w->ingame->no_money->time_anim->seconds <= 0.8) {
        draw_sprite(w->win, w->ingame->no_money->sprite);
    }
}
