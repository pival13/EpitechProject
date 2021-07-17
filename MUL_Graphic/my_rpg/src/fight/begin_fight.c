/*
** EPITECH PROJECT, 2019
** begin fight
** File description:
** begin fight
*/

#include "my.h"

void begin_fight(rpg_t *r, int salut, int *which)
{
    sfRenderWindow_clear(r->win, sfBlack);
    sfSprite_setScale(r->fight->sprite[salut], (sfVector2f){(double)sfRender\
Window_getSize(r->win).x / sfSprite_getLocalBounds(r->fight->sprite[salut]).\
width , (double)sfRenderWindow_getSize(r->win).x / sfSprite_getLocalBounds\
(r->fight->sprite[salut]).width});
    sfSprite_setPosition(r->fight->sprite[salut], (sfVector2f){0, sfRenderWindo\
w_getSize(r->win).y - sfSprite_getGlobalBounds(r->fight->sprite[salut]).height\
});
    sfRenderWindow_drawSprite(r->win, r->fight->sprite[salut], NULL);

    if (r->fight->resultat == 0)
        return;
    for (int i = 0; i < 5+r->fight->nb_ennemies; i++) {
        if (i >= 5)
            find_coeff(r, i, which[i-5]);
        else
            place_all(r, i);
    }
}