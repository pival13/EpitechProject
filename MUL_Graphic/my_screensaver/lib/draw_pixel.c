/*
** EPITECH PROJECT, 2018
** create_pixel
** File description:
** Draw pixel in a window
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "csfml.h"

void put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y\
, sfColor color)
{
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4] = color.r;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 1] \
= color.g;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 2] \
= color.b;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 3] \
= color.a;
}
