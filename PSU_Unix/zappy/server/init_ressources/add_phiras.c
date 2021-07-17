/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** add_phiras
*/

#include "server.h"

/**
 * @brief Add phiras to map's cell.
 *
 * @param map Map's cell.
 */
void add_phiras(map_t *map, int *rock)
{
    if (map->ressources.phiras >= 3)
        return;
    if (*rock == 5) {
        map->ressources.phiras += 1;
        *rock = 0;
    }
}

/**
 * @brief Add phiras to map's cell.
 *
 * @param map Map's cell.
 */
void add_phiras_simple(map_t *map)
{
    if (map->ressources.phiras < 3)
        map->ressources.phiras += 1;
}