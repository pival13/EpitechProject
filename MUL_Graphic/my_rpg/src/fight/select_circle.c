/*
** EPITECH PROJECT, 2019
** select circle
** File description:
** select circle
*/

#include "my.h"

void s_select(rpg_t *r, int nb)
{
    float pos[2];

    pos[0] = sfSprite_getPosition(r->fight->sprite[nb]).x;
    pos[1] = sfSprite_getPosition(r->fight->sprite[nb]).y;
    sfCircleShape_setOutlineColor(r->fight->circle, sfRed);
    sfCircleShape_setOutlineThickness(r->fight->circle, 3);
    sfCircleShape_setPosition(r->fight->circle, (sfVector2f){pos[0], pos[1]});
    sfCircleShape_setRadius(r->fight->circle, 100);
    sfCircleShape_setFillColor(r->fight->circle, sfTransparent);
    sfRenderWindow_drawCircleShape(r->win, r->fight->circle, NULL);
}