/*
** EPITECH PROJECT, 2019
** obj_init.c
** File description:
** obj init
*/

#include "my.h"

void obj_init(obj_t *obj)
{
    obj->content = NULL;
    obj->text = NULL;
    obj->font = NULL;
    obj->sprite = NULL;
    obj->texture = NULL;
    obj->time_anim = NULL;
    obj->sound = NULL;
    obj->music = NULL;
    obj->buffer = NULL;
}
