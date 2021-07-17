/*
** EPITECH PROJECT, 2019
** draw.c
** File description:
** draw sprite shortened
*/

#include "my.h"

void draw_sprite(sfRenderWindow *win, sfSprite *sprite)
{
    sfRenderWindow_drawSprite(win, sprite, NULL);
}

void draw_sftext(sfRenderWindow *win, sfText *text)
{
    sfRenderWindow_drawText(win, text, NULL);
}
