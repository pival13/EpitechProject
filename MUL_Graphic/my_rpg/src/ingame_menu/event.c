/*
** EPITECH PROJECT, 2019
** ingame_menu.c
** File description:
** display ingame menue
*/

#include "my.h"

void exchange_money(rpg_t *w, int gold, int perso)
{
    if (gold <= w->inventory.gold) {
        w->inventory.gold -= gold;
        w->player[perso].stat.exp += gold / 5;
        w->player[perso].level = get_level(w->player[perso].stat.exp);
        reset_time(w->ingame->bought->time_anim, w->clock);
    } else {
        reset_time(w->ingame->no_money->time_anim, w->clock);
    }
}

void shop_events(rpg_t *w)
{
    if (KEY_I() && w->ingame->key_pos2 == 1) {
        exchange_money(w, 10, w->ingame->key_pos);
    }
    for (int i = 0; i < 5; i++) {
        if (click_button(w->cursor, w->ingame->shop[i], w->event))
            exchange_money(w, 10, i);
    }
}

void event_ingame_menu(rpg_t *w, int *i)
{
    get_time(w->ingame->buttons[SAVE_IG]->time_move, w->clock);
    if (click_button(w->cursor, w->ingame->buttons[QUIT_IG], w->event) == 1) {
        change_page(w, MENU);
        *i = 0;
    }
    if (click_button\
(w->cursor, w->ingame->buttons[SETTINGS_IG], w->event) == 1)
        change_page(w, SETT);
    if (click_button(w->cursor, w->ingame->buttons[INVENTORY], w->event) == 1)
        change_page(w, CH);
    if (click_button(w->cursor, w->ingame->buttons[SAVE_IG], w->event) == 1) {
        save_save(w);
        reset_time(w->ingame->buttons[SAVE_IG]->time_move, w->clock);
    }
    if (click_button(w->cursor, w->ingame->buttons[QUEST], w->event) == 1)
        change_page(w, QM);
}
