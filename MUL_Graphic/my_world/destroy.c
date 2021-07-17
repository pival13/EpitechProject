/*
** EPITECH PROJECT, 2019
** destroy
** File description:
** destroy
*/

#include "my_world.h"
#include <stdlib.h>

void destroy2(world_t *w)
{
    for (int i = 0; w->map[i] != NULL; i++) {
        for (int j = 0; w->map[i+1] != NULL && w->map[i][j+1].height != -1\
00; j++)
            sfConvexShape_destroy(w->map[i][j].shape);
        free(w->map[i]);
    }
    free(w->map);
    for (int i = 0; i != 7; i++)sfTexture_destroy(w->texture[i]);
    sfFont_destroy(w->font);
    sfRenderWindow_destroy(w->window);
    for (int i = 0; i != 2; i++) {
        sfMusic_stop(w->music[i]);
        sfMusic_setLoop(w->music[i], sfFalse);
        sfMusic_destroy(w->music[i]);
    }
    free(w);
}

void destroy(world_t *w)
{
    sfCircleShape_destroy(w->circle);
    for (int i = 0; i != 12; ++i)
        sfRectangleShape_destroy(w->page[1].rbutton[i]);
    for (int i = 0; i != 4; ++i)
        sfTexture_destroy(w->page[1].tbutton[i]);
    for (int i = 0; i != 2; ++i) {
        sfTexture_destroy(w->page[i].tbackground);
        sfSprite_destroy(w->page[i].background);
        for (int j = 0; w->page[i].text[j] != NULL; ++j) {
            sfText_destroy(w->page[i].text[j]);
        }
        free(w->page[i].text);
    }
    free(w->page);
    destroy2(w);
}
