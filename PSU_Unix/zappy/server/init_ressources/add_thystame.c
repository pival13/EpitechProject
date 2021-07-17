/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** add_thystame
*/

#include "server.h"

/**
 * @brief Add thystame to a map's cell.
 *
 * @param map Map's cell.
 */
void add_thystame(map_t *map, int *rock)
{
    if (map->ressources.thystame >= 3)
        return;
    if (*rock == 25) {
        map->ressources.thystame += 1;
        *rock = 0;
    }
}

/**
 * @brief Add thystame to a map's cell.
 *
 * @param map Map's cell.
 */
void add_thystame_simple(map_t *map)
{
    if (map->ressources.thystame < 3)
        map->ressources.thystame += 1;
}