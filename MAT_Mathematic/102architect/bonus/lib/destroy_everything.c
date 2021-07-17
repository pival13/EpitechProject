/*
** EPITECH PROJECT, 2018
** destroy_everything
** File description:
** destroy what is create with create_struct_window
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "csfml.h"

int destroy_everything(window_t *w)
{
    free(w->fb->pixel);
    free(w->fb);
    sfTexture_destroy(w->texture);
    sfSprite_destroy(w->sprite);
    sfRenderWindow_destroy(w->window);
    free(w);
}
