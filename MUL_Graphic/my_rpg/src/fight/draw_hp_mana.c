/*
** EPITECH PROJECT, 2019
** mana and health bar
** File description:
** bar
*/

#include "my.h"

void draw_rectangle2(rpg_t *r, int which)
{
    sfRectangleShape_setSize(r->fight->shape, (sfVector2f){104, 26});
    sfRectangleShape_setFillColor(r->fight->shape, sfBlack);
    sfRectangleShape_setPosition(r->fight->shape, (sfVector2f){
    sfSprite_getPosition(r->fight->sprite[which]).x,
    sfSprite_getPosition(r->fight->sprite[which]).y + 40});
}

void draw_rectangle(rpg_t *r, int which)
{
    draw_rectangle2(r, which);
    if (r->player[which].stat.hp[0] > 0)
        sfRenderWindow_drawRectangleShape(r->win, r->fight->shape, NULL);
    sfRectangleShape_setSize(r->fight->shape, (sfVector2f){100 * r->player[whi\
ch].stat.hp[0] / r->player[which].stat.hp[1], 10});
sfRectangleShape_setPosition(r->fight->shape, (sfVector2f){sfSprite_getPosi\
tion(r->fight->sprite[which]).x + 2, sfSprite_getPosition(r->fight->sprite\
[which]).y + 42});
    sfRectangleShape_setFillColor(r->fight->shape, sfRed);
    if (r->player[which].stat.hp[0] > 0)
        sfRenderWindow_drawRectangleShape(r->win, r->fight->shape, NULL);
    sfRectangleShape_setSize(r->fight->shape, (sfVector2f){100 * r->player[whi\
ch].stat.mp[0] / r->player[which].stat.mp[1], 10});
    sfRectangleShape_setPosition(r->fight->shape, (sfVector2f){sfSprite_getPosi\
tion(r->fight->sprite[which]).x + 2, sfSprite_getPosition(r->fight->sprite\
[which]).y + 54});
    sfRectangleShape_setFillColor(r->fight->shape, sfBlue);
    if (r->player[which].stat.mp[0] > 0)
        sfRenderWindow_drawRectangleShape(r->win, r->fight->shape, NULL);
}
