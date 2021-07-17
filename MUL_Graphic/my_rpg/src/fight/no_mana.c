/*
** EPITECH PROJECT, 2019
** no_mana.c
** File description:
** no mana
*/

#include "my.h"

void draw_mana(rpg_t *w)
{
    static int i = 0;

    if (i == 0) {
        sfSprite_setTexture(w->fight->nomana_msg, w->textures[NOMANA], sfTrue);
        sprite_set_position(w->fight->nomana_msg, 860, 440);
        i = 1;
    }
    if (w->fight->nomana == 1) {
        reset_time(w->fight->time_mana, w->clock);
        w->fight->nomana = 0;
    }
    get_time(w->fight->time_mana, w->clock);
    if (w->fight->time_mana->seconds < 1.5) {
        draw_sprite(w->win, w->fight->nomana_msg);
    }
}

void draw_fuite(rpg_t *w)
{
    static int i = 0;

    if (i == 0) {
        sfSprite_setTexture(w->fight->fuite_msg, w->textures[FUITE], sfTrue);
        sprite_set_position(w->fight->fuite_msg, 860, 440);
        i = 1;
    }
    if (w->fight->fuite == 1) {
        reset_time(w->fight->time_fuite, w->clock);
        w->fight->fuite = 0;
    }
    get_time(w->fight->time_fuite, w->clock);
    if (w->fight->time_fuite->seconds < 1.5) {
        draw_sprite(w->win, w->fight->fuite_msg);
    }
}
