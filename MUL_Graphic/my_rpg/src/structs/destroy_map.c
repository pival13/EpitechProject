/*
** EPITECH PROJECT, 2019
** destroy_map.c
** File description:
** destroy map
*/

#include "my.h"

void destroy_map(map_t *map)
{
    sfConvexShape_destroy(map->shape);
    sfSprite_destroy(map->diamond);
    free(map);
}
