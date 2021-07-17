/*
** EPITECH PROJECT, 2019
** place allies
** File description:
** place allies
*/

#include "my.h"

void place_all(rpg_t *r, int which)
{
    float sub = which;

    r->fight->rect = (sfIntRect){0, 0, sfTexture_getSize(r->player[which].textu\
re).x / r->player[which].nb_sprite, sfTexture_getSize(r->player[which].texture)\
.y};
    sfSprite_setTextureRect(r->fight->sprite[which], r->fight->rect);
    sfSprite_setPosition(r->fight->sprite[which], (sfVector2f){(0.25) * sfRende\
rWindow_getSize(r->win).x + (sfTexture_getSize(r->player[which].texture).y / \
r->player[which].nb_sprite) - (95 * sub), (sfRenderWindow_getSize(r->win).y * \
(0.45)) + (sub * 40)});
    draw_rectangle(r, which);
    if ((r->fight->skill == 0 || which != r->fight->turn) && r->player[which].\
stat.hp[0] > 0)
        sfRenderWindow_drawSprite(r->win, r->fight->sprite[which], NULL);
}