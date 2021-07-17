/*
** EPITECH PROJECT, 2019
** set_position.c
** File description:
** set position
*/

#include "my.h"

void obj_set_position(obj_t *obj, float x, float y)
{
    obj->pos.x = x;
    obj->pos.y = y;
    sfSprite_setPosition(obj->sprite, obj->pos);
}

void obj_move(obj_t *obj, float x, float y)
{
    obj->pos.x += x;
    obj->pos.y += y;
    sfSprite_setPosition(obj->sprite, obj->pos);
}

void obj_set_position_text(obj_t *obj, float x, float y)
{
    obj->pos.x = x;
    obj->pos.y = y;
    sfText_setPosition(obj->text, obj->pos);
}

void obj_move_text(obj_t *obj, float x, float y)
{
    obj->pos.x += x;
    obj->pos.y += y;
    sfText_setPosition(obj->text, obj->pos);
}
