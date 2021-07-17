/*
** EPITECH PROJECT, 2019
** set_visible.c
** File description:
** set visible and invisible functions
*/

#include "my.h"

void set_visible(sfSprite *sprite)
{
    sfColor visible = {255, 255, 255, 255};

    sfSprite_setColor(sprite, visible);
}

void set_invisible(sfSprite *sprite)
{
    sfColor invisible = {255, 255, 255, 0};

    sfSprite_setColor(sprite, invisible);
}
