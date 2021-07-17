/*
** EPITECH PROJECT, 2019
** set_alpha.c
** File description:
** set alpha
*/

#include "my.h"

void set_alpha(sfSprite *sprite, float alpha)
{
    sfColor visible = {255, 255, 255, alpha};

    sfSprite_setColor(sprite, visible);
}
