/*
** EPITECH PROJECT, 2018
** raw_bloc
** File description:
** draw a full square
*/

#include "csfml.h"
#include <SFML/Graphics.h>

void draw_bloc(framebuffer_t *fb, sfVector2f position, unsigned int size, \
sfColor color)
{
    for (int x = position.x; x != position.x + size; x++)
        for (int y = position.y; y != position.y + size; y++)
            put_pixel(fb, x, y, color);
}
