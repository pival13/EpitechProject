/*
** EPITECH PROJECT, 2019
** mod_scale.c
** File description:
** mod scale funcs
*/

#include "my.h"

void mod_scale(obj_t *obj, float n)
{
    sfSprite *sprite = obj->sprite;
    sfVector2f scale;

    scale.x = n;
    scale.y = n;
    sfSprite_setScale(sprite, scale);
    obj->scale = scale;
}

void mod_scale_p(obj_t *obj, float n)
{
    sfSprite *sprite = obj->sprite;
    sfVector2f scale = obj->scale;

    scale.x += n;
    scale.y += n;
    sfSprite_setScale(sprite, scale);
    obj->scale = scale;
}
