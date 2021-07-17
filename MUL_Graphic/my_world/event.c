/*
** EPITECH PROJECT, 2019
** condition
** File description:
** condition
*/

#include "my_world.h"
#include <math.h>

void resize_elements(world_t *w)
{
    edit_map(w, (float[2]){0, 0}, (float[2]){0, 0}, 0);
    sfSprite_setScale(w->page[0].background, COEFF(w->page[0].tbackground));
    sfSprite_setScale(w->page[1].background, COEFF(w->page[1].tbackground));
    sfCircleShape_setScale(w->circle, (sfVector2f){BSIZE(width)/SIZE(x) , BSI\
ZE(height)/SIZE(y)});
}

void condition(world_t *w, int i)
{
    while (sfRenderWindow_pollEvent(w->window, &(w->event))) {
        if (w->event.type == sfEvtClosed || i == -1 || (w->event.key.code == \
sfKeyEscape && w->event.type == sfEvtKeyPressed))
            sfRenderWindow_close(w->window);
        if (w->event.type == sfEvtResized) {
            resize_elements(w);
        }
    }
}
