/*
** EPITECH PROJECT, 2018
** screensaver7
** File description:
** Circle into circle
*/

#include "csfml.h"
#include <SFML/Graphics.h>
#define CHOOSE(nb, size) (nb < size) ? (nb) : (size)

int ss6(framebuffer_t *fb, sfVector2f *center, int a[2], sfColor color)
{
    int size = CHOOSE((CHOOSE(center->x-1, SCREEN_X-center->x-1))\
, (CHOOSE(center->y-1, SCREEN_Y-center->y-1)));

    a[0]++;
    if (a[0]%100 == 0) {
        a[1]++;
        a[1] %= size/5;
        for (int i = 0; i != a[1]; i++);
        draw_circle(fb, *center, size-5*a[1], color);
    }
}
