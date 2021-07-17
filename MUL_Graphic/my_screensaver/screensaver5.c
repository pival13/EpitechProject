/*
** EPITECH PROJECT, 2018
** screensaver5
** File description:
** fireworks
*/

#include "csfml.h"
#include <SFML/Graphics.h>
#include <math.h>
#include <stdlib.h>

int ss5(framebuffer_t *fb, sfVector2f *ball, int nothing[2], sfColor color)
{
    int i = rand()%100;
    sfVector2f circle[5] = {{200, 200}, {200, 200}, {200, 200}, {200, 200}\
, {200, 200}};
    int a[5] = {22, 26, 32, 40, 50};

    dissolve(fb);
    if (i == 0) {
        draw_circle(fb, *ball, 20, color);
        for (int j = 0; j != 24; j++)
            for (int k = 0; k != 5; k++) {
                circle[k].x = ball->x + a[k] * cos(15*j*3.14/180);
                circle[k].y = ball->y + a[k] * sin(15*j*3.14/180);
                draw_circle(fb, circle[k], k+1, color);
            }
    }
    ball->x = rand()%(SCREEN_X-110) + 55;
    ball->y = rand()%(SCREEN_Y-110) + 56;
}
