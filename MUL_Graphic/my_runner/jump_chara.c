/*
** EPITECH PROJECT, 2018
** jump_chara
** File description:
** make jump the chara
*/

#include "csfml.h"

void jump_chara(sfClock *clock, window_t *w)
{
    int h = w->obj[PLAYER]->pos.y / 40;

    if (w->mouse == 1) {
        anim_obj(clock, w->obj[PLAYER], 9, 10);
        move_obj(clock, w->obj[PLAYER], 0, -120);
        if (sfSprite_getPosition(w->obj[PLAYER]->sprite).y < (h-1)*40-20) {
            w->mouse = 0;
            sfClock_restart(w->jump);
            w->obj[PLAYER]->pos.y -= 40;
        }
    }
}

void check_chara(window_t *w)
{
    if (w->mouse == 0) {
        sfClock_restart(w->jump);
        move_obj(w->clock, w->obj[PLAYER], 0, 0);
    }
}

void fall_chara(window_t *w)
{
    int h = w->obj[PLAYER]->pos.y / 40;

    if (((w->map[h][4].type == ' ' || w->map[h][4].type == '\0') && h < 10 \
&& w->mouse == 0) || w->mouse == 2) {
        if ((w->map[h][5].type == '#' && w->obj[PLAYER]->rect.width*4/5 + w-> \
obj[PLAYER]->pos.x >= w->map[h][5].move.x && sfSprite_getPosition(w->obj\
[PLAYER]->sprite).y >= (h)*40 - 10) || w->map[h][4].type == '#') {
            w->mouse = 0;
            return;
        }
        w->mouse = 2;
        anim_obj(w->jump, w->obj[PLAYER], 11, 12);
        move_obj(w->jump, w->obj[PLAYER], 0, 150);
        if (sfSprite_getPosition(w->obj[PLAYER]->sprite).y >= (h+1)*40) {
            w->mouse = 0;
            w->obj[PLAYER]->pos.y += 40;
        }
    }
    check_chara(w);
}
