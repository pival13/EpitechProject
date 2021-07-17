/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** add_mendiane
*/

#include "server.h"

/**
 * @brief Add mendiane to map's cell.
 *
 * @param map Map's cell.
 */
void add_mendiane(map_t *map, int *rock)
{
    if (map->ressources.mendiane >= 3)
        return;
    if (*rock == 6) {
        map->ressources.mendiane += 1;
        *rock = 0;
    }
}

/**
 * @brief Add mendiane to map's cell.
 *
 * @param map Map's cell.
 */
void add_mendiane_simple(map_t *map)
{
    if (map->ressources.mendiane < 3)
        map->ressources.mendiane += 1;
}
