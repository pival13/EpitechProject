/*
** EPITECH PROJECT, 2018
** create struct window
** File description:
** Create the struct window_t
*/

#include "csfml.h"
#include <stdlib.h>

window_t *create_struct_window(int width, int height, char *name, char *file)
{
    window_t *window = malloc(sizeof(window_t));

    window->mode.width = width;
    window->mode.height = height;
    window->mode.bitsPerPixel = 32;
    window->window = sfRenderWindow_create(window->mode, name, sfDefaultStyle, \
NULL);
    window->texture = sfTexture_createFromFile(file, NULL);
    window->sprite = sfSprite_create();
    sfSprite_setTexture(window->sprite, window->texture, sfFalse);
    sfRenderWindow_setFramerateLimit(window->window, 100);
    return (window);
}
