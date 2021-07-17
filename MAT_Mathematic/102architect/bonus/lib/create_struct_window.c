/*
** EPITECH PROJECT, 2018
** create struct window
** File description:
** Create the struct window_t
*/

#include "csfml.h"
#include <stdlib.h>

window_t *create_struct_window(int width, int height, char *name)
{
    window_t *window;

    window = malloc(sizeof(window_t));
    window->mode.width = width;
    window->mode.height = height;
    window->mode.bitsPerPixel = 32;
    window->window = sfRenderWindow_create(window->mode, name, sfDefaultStyle, \
NULL);
    window->texture = sfTexture_create(width, height);
    window->sprite = sfSprite_create();
    window->fb = framebuffer_create(width, height);
    return (window);
}
