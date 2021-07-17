/*
** EPITECH PROJECT, 2018
** sceensaver2
** File description:
** draw multicolor wave of circle
*/

#include "csfml.h"
#include <SFML/Graphics.h>
#include <math.h>

int ss2(framebuffer_t *fb, sfVector2f *ball, int a[2], sfColor color)
{
    for (int i = 1; i <= SCREEN_Y; i++)
        for (int j = 1; j <= SCREEN_X; j++) {
            if (fb->pixel[((fb->width) * (i - 1) + j - 1) * 4 + 3] > 0)
                fb->pixel[((fb->width) * (i - 1) + j - 1) * 4 + 3] -= 1;
        }
    (ball->y > SCREEN_Y - 25) ? (a[1] = 1, ball->y = SCREEN_Y - 25) : (a[1]);
    (ball->y < 0 + 25 + 3) ? (a[1] = -1, ball->y = 25 + 3) : (a[1]);
    ball->x = SCREEN_X / 2 + SCREEN_X / 2 * sin(a[0]);
    (a[1] == 1) ? (ball->y--) : (ball->y++);
    a[0]++;
    a[0] %= SCREEN_X;
    draw_circle(fb, *ball, 25, color);
}
