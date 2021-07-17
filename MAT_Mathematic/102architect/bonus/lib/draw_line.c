/*
** EPITECH PROJECT, 2018
** draw_line
** File description:
** draw a line from two points
*/

#include "csfml.h"
#include <SFML/Graphics.h>
#include <math.h>

#define COEFX (a.y-b.y)/(a.x-b.x)
#define COEFY (a.x-b.x)/(a.y-b.y)

int draw_line(framebuffer_t *fb, sfVector2f a, sfVector2f b, sfColor color)
{
    if (fabs(b.x-a.x) >= fabs(b.y-a.y))
        for (int i = a.x; i != b.x;) {
            put_pixel(fb, i, COEFX*i-COEFX*a.x+a.y, color);
            (a.x < b.x) ? (i++) : (i--);
        }
    else
        for (int i = a.y; i != b.y;) {
            put_pixel(fb, COEFY*i-COEFY*a.y+a.x, i, color);
            (a.y < b.y) ? (i++) : (i--);
        }
    put_pixel(fb, b.x, b.y, color);
}
