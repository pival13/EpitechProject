/*
** EPITECH PROJECT, 2018
** destroy_everything
** File description:
** destroy what is create with create_struct_window
*/

#include <stdlib.h>
#include "csfml.h"
#include "my.h"

map_t **destroy_map(map_t **map)
{
    if (map != NULL) {
        for (int i = 0; map[i] != NULL; i++)
            free(map[i]);
        free(map);
    }
    map = NULL;
    return (map);
}

void destroy_everything(window_t *w)
{
    sfRenderWindow_destroy(w->window);
    sfClock_destroy(w->clock);
    sfClock_destroy(w->jump);
    sfMusic_destroy(w->music);
    sfMusic_destroy(w->sound);
    free(w);
    w->map = destroy_map(w->map);
    for (int i = 0; i != 7; i++) {
        sfTexture_destroy(w->obj[i]->texture);
        sfSprite_destroy(w->obj[i]->sprite);
        free(w->obj[i]);
    }
    free(w->obj);
}
