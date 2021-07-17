/*
** EPITECH PROJECT, 2019
** center_obj.c
** File description:
** center obj
*/

#include "my.h"

void center_obj(obj_t *obj)
{
    obj->origin.x = obj->rect.width / 2;
    obj->origin.y = obj->rect.height / 2;
    sfSprite_setOrigin(obj->sprite, obj->origin);
}
