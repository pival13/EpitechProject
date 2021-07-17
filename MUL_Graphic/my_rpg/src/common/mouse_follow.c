/*
** EPITECH PROJECT, 2019
** mouse_follow.c
** File description:
** mouse follow
*/

#include "my.h"

void mouse_follow(rpg_t *w)
{
    sfVector2i posi = sfMouse_getPositionRenderWindow(w->win);
    sfVector2f posf = {posi.x, posi.y};

    obj_set_position(w->cursor, posf.x, posf.y);
}
