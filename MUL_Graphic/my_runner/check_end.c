/*
** EPITECH PROJECT, 2019
** check_end
** File description:
** check the end of the programm
*/

#include "csfml.h"
#include <stdio.h>

void finish_game(window_t *w, float time, int start, int end)
{
    while (sfClock_getElapsedTime(w->jump).microseconds < 1000000*time) {
        anim_obj(w->jump, w->obj[PLAYER], start, end);
        draw_window(w);
    }
    while (w->event.type != sfEvtClosed && w->event.type != sfEvtKeyPressed \
&& w->event.type != sfEvtMouseButtonPressed)
        sfRenderWindow_pollEvent(w->window, &w->event);
    sfRenderWindow_close(w->window);
}

void check_end(window_t *w)
{
    int h = (int)(sfSprite_getPosition(w->obj[PLAYER]->sprite).y)/40-1;
    int nb_0 = 0;

    if (w->obj[PLAYER]->pos.y > 400)
        finish_game(w, 1, 21, 21);
    if ((w->map[h][5].type != ' ' && w->map[h][5].type != '\0') && w->obj\
[PLAYER]->pos.x+w->obj[PLAYER]->rect.width > w->map[h][5].move.x)
        finish_game(w, 0.3, 18, 20);
    if (w->map[h+1][4].type == 'M')
        finish_game(w, 0.3, 13, 15);
    for (int i = 0; w->map[i] != NULL; i++) {
        if (w->map[i][0].type == '\0')
            nb_0++;
        for (int j = 0; w->map[i][j].type != '\0'; j++)
            if (w->map[i][j+1].type == '\0' && j+1 < (int)sfRenderWindow_\
getSize(w->window).x/40)
                nb_0++;
    }
    if (nb_0 >= 10)
        finish_game(w, 1, 16, 17);
}
