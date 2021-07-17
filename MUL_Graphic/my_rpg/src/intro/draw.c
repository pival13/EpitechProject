/*
** EPITECH PROJECT, 2019
** draw.c
** File description:
** draw intro
*/

#include "my.h"

void draw_intro(rpg_t *w)
{
    draw_sprite(w->win, w->intro->bgd2->sprite);
    draw_sprite(w->win, w->intro->bgd->sprite);
    draw_sprite(w->win, w->intro->narrator->sprite);
    draw_sprite(w->win, w->intro->f_dialogue->sprite);
    draw_sprite(w->win, w->intro->f_choices->sprite);
    draw_sftext(w->win, w->intro->dialogue);
    for (int i = 0; i < 3; i++)
        draw_sftext(w->win, w->intro->choices[i]);
    draw_sftext(w->win, w->intro->point);
    draw_sprite(w->win, w->intro->key_cursor->sprite);
}
