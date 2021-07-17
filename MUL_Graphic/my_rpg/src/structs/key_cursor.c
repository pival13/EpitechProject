/*
** EPITECH PROJECT, 2019
** key_cursor.c
** File description:
** key cursor
*/

#include "my.h"

obj_t *create_key_cursor(sfClock *clock)
{
    obj_t *cursor = create_obj_t_sprite(clock, "data/others/cursor.png", NULL);

    return (cursor);
}
