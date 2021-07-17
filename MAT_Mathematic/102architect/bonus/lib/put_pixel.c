/*
** EPITECH PROJECT, 2018
** create_pixel
** File description:
** Draw pixel in a window
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "csfml.h"

void put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y, sfColor color)
{
    int red = color.r;
    int green = color.g;
    int blue = color.b;
    int alpha = color.a;

    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4] = red;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 1] = green;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 2] = blue;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 3] = alpha;
}
