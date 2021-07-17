/*
** EPITECH PROJECT, 2018
** screensaver3
** File description:
** Draw random circle and square
*/

#include "csfml.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

int ss3(framebuffer_t *fb, sfVector2f *ball, int a[2], sfColor color)
{
    for (int i = 1; i <= SCREEN_Y; i++)
        for (int j = 1; j <= SCREEN_X; j++)
            if (fb->pixel[((fb->width) * (i - 1) + j - 1) * 4 + 3] > 0)
                fb->pixel[((fb->width) * (i - 1) + j - 1) * 4 + 3] -= 1;
    ball->x += 50;
    ball->y += 50;
    draw_circle(fb, *ball, rand()%50, color);
    ball->x = rand()%(SCREEN_X-48) + 1;
    ball->y = rand()%(SCREEN_Y-47) + 1;
    draw_bloc(fb, *ball, rand()%51, color);
    ball->x = rand()%(SCREEN_X-100);
    ball->y = rand()%(SCREEN_Y-100);
}
