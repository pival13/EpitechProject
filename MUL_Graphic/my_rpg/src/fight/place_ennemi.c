/*
** EPITECH PROJECT, 2019
** place ennemy
** File description:
** place enemy
*/

#include "my.h"

void find_coeff(rpg_t *r, int which, int n)
{
    float coeff = 0;
    float sub = (5 - r->fight->nb_ennemies) / 2 + which;

    coeff = (sfTexture_getSize(r->textures[n]).y);
    coeff = 200 / coeff;
    sfSprite_setScale(r->fight->sprite[which], (sfVector2f){coeff, coeff});
    sfSprite_setPosition(r->fight->sprite[which], (sfVector2f){(0.45
    * sfRenderWindow_getSize(r->win).x) - (sfRenderWindow_getSize
    (r->win).x / 6) + (120 * sub), (sfRenderWindow_getSize(r->win).y
    * (0.3) + (sub*40))});
    if (r->mob[which-5].stat.hp > 0)
        sfRenderWindow_drawSprite(r->win, r->fight->sprite[which], NULL);
}
