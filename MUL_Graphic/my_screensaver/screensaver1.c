/*
** EPITECH PROJECT, 2018
** sceensaver1
** File description:
** draw multicolor line
*/

#include "csfml.h"
#include <SFML/Graphics.h>

int ss1(framebuffer_t *fb, sfVector2f *ball, int a[2], sfColor color)
{
    (ball->x > SCREEN_X - 25) ? (a[0] = 1, ball->x = SCREEN_X - 25) : (a[0]);
    (ball->x < 0 + 25 + 1) ? (a[0] = -1, ball->x = 26) : (a[0]);
    (ball->y > SCREEN_Y - 25) ? (a[1] = 1, ball->y = SCREEN_Y - 25) : (a[1]);
    (ball->y < 0 + 25 + 2) ? (a[1] = -1, ball->y = 27) : (a[1]);
    (a[0] == 1) ? (ball->x--) : (ball->x++);
    (a[1] == 1) ? (ball->y--) : (ball->y++);
    draw_circle(fb, *ball, 25, color);
}
