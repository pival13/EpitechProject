/*
** EPITECH PROJECT, 2019
** mod.c
** File description:
** mod sprite
*/

#include "my.h"

void sprite_set_scale(sfSprite *sprite, float x, float y)
{
    sfVector2f scale = {x, y};

    sfSprite_setScale(sprite, scale);
}

void sprite_set_position(sfSprite *sprite, float x, float y)
{
    sfVector2f position = {x, y};

    sfSprite_setPosition(sprite, position);
}

void sprite_move(sfSprite *sprite, float x, float y)
{
    sfVector2f position = {x, y};

    sfSprite_move(sprite, position);
}

void sprite_set_origin(sfSprite *sprite, float x, float y)
{
    sfVector2f origin = {x, y};

    sfSprite_setOrigin(sprite, origin);
}
