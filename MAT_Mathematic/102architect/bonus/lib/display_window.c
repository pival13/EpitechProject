/*
** EPITECH PROJECT, 2018
** display_window
** File description:
** update the texture with the fb, and draw all
*/

#include <SFML/Graphics.h>
#include "csfml.h"

int display_window(window_t *w)
{
    sfSprite_setTexture(w->sprite, w->texture, sfFalse);
    sfTexture_updateFromPixels(w->texture, w->fb->pixel, SCREEN_X, SCREEN_Y, 0, 0);
    sfRenderWindow_clear(w->window, sfBlack);
    sfRenderWindow_drawSprite(w->window, w->sprite, NULL);
    sfRenderWindow_display(w->window);
}
