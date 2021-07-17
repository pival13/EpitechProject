/*
** EPITECH PROJECT, 2018
** light_dissolve
** File description:
** Erase lightly the screen
*/

#include "csfml.h"
#include <SFML/Graphics.h>

void dissolve(framebuffer_t *fb)
{
    for (int i = 1; i <= SCREEN_Y; i++)
        for (int j = 1; j <= SCREEN_X; j++)
            if (fb->pixel[((fb->width) * (i - 1) + j - 1) * 4 + 3] > 0)
                fb->pixel[((fb->width) * (i - 1) + j - 1) * 4 + 3] -= 1;
}
