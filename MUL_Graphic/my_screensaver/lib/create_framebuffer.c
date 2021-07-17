/*
** EPITECH PROJECT, 2018
** create_framebuffer
** File description:
** create the framebuffer
*/

#include "csfml.h"
#include <stdlib.h>
#include <SFML/Graphics.h>

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height)
{
    framebuffer_t *framebuffer;

    framebuffer = malloc(sizeof(framebuffer_t));
    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->pixel = malloc(sizeof(unsigned int) * width * height * 4);
    return (framebuffer);
}
