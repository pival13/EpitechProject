/*
** EPITECH PROJECT, 2019
** cut.c
** File description:
** cut for animation
*/

#include "my.h"

int cut_animation(obj_t *obj, int x, int y)
{
    if (x <= 0 || y <= 0)
        return (84);
    obj->rect = sfSprite_getTextureRect(obj->sprite);
    obj->rect.width /= x;
    obj->rect.height /= y;
    obj->rect.left = 0;
    obj->rect.top = 0;
    sfSprite_setTextureRect(obj->sprite, obj->rect);
    center_obj(obj);
    return (0);
}
