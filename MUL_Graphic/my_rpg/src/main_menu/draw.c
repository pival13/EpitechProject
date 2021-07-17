/*
** EPITECH PROJECT, 2019
** draw.c
** File description:
** draw
*/

#include "my.h"

void draw_main_menu(rpg_t *w)
{
    get_time(w->mm->no_save->time_anim, w->clock);
    get_time(w->mm->deleted->time_anim, w->clock);
    sfRenderWindow_drawSprite(w->win, w->mm->bgd->sprite, NULL);
    for (int i = 0; i < 7; i++)
        sfRenderWindow_drawSprite(w->win, w->mm->buttons[i]->sprite, NULL);
    sfRenderWindow_drawSprite(w->win, w->mm->title->sprite, NULL);
    if (w->mm->no_save->time_anim->seconds <= 1)
        sfRenderWindow_drawSprite(w->win, w->mm->no_save->sprite, NULL);
    if (w->mm->deleted->time_anim->seconds <= 1)
        sfRenderWindow_drawSprite(w->win, w->mm->deleted->sprite, NULL);
}
