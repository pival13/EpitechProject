/*
** EPITECH PROJECT, 2019
** draw.c
** File description:
** draw settings
*/

#include "my.h"

void draw_settings(rpg_t *w)
{
    sfRenderWindow_drawSprite(w->win, w->mm->bgd->sprite, NULL);
    sfRenderWindow_drawSprite(w->win, w->sett->sound_icon->sprite, NULL);
    sfRenderWindow_drawSprite(w->win, w->sett->music_icon->sprite, NULL);
    for (int i = 0; i < 10; i++) {
        sfRenderWindow_drawSprite(w->win, w->sett->sound_bar[i]->sprite, NULL);
        sfRenderWindow_drawSprite(w->win, w->sett->music_bar[i]->sprite, NULL);
    }
    sfRenderWindow_drawSprite(w->win, w->sett->return_button->sprite, NULL);
}
