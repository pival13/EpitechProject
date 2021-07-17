/*
** EPITECH PROJECT, 2018
** screensaver4
** File description:
** Line
*/

#include "csfml.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

int ss4(framebuffer_t *fb, sfVector2f *ball, int a[2], sfColor color)
{
    for (int i = 1; i <= SCREEN_Y; i++)
        for (int j = 1; j <= SCREEN_X; j++)
            if (fb->pixel[((fb->width) * (i - 1) + j - 1) * 4 + 3] > 0)
                fb->pixel[((fb->width) * (i - 1) + j - 1) * 4 + 3] -= 1;
    sfVector2f center = {SCREEN_X/2, SCREEN_Y*3/5};
    if (rand()%5 < 2) {
        ball->x = rand()%2 * (SCREEN_X-1) + 1;
        ball->y = rand()%SCREEN_Y + 1;
    } else {
        ball->x = rand()%SCREEN_X + 1;
        ball->y = rand()%2 * (SCREEN_Y-1) + 1;
    }
    draw_line(fb, *ball, center, color);
}
