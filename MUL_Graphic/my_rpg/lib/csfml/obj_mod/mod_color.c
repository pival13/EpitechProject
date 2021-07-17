/*
** EPITECH PROJECT, 2019
** mod_color.c
** File description:
** mod color csfml
*/

#include "my.h"

void mod_color(sfSprite *sprite, float re, float gr, float bl)
{
    sfColor color = {re, gr, bl, 255};

    sfSprite_setColor(sprite, color);
}
