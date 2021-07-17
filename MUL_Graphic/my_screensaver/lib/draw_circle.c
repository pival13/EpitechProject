/*
** EPITECH PROJECT, 2018
** draw_circle
** File description:
** draw a circle from its center and its radius
*/

#include <SFML/Graphics.h>
#include "csfml.h"
#include <math.h>

int draw_circle(framebuffer_t *fb, sfVector2f center, int radius, sfColor color)
{
    for (float y = center.y - radius; y <= center.y + radius; y += 1)
        for (float x = center.x - radius; x <= center.x + radius; x += 1)
            if (((PT_X)*(PT_X) + (PT_Y)*(PT_Y)) <= radius*radius)
                put_pixel(fb, x, y, color);
}
