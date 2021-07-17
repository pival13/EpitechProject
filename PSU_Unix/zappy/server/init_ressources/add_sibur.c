/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** add_sibur
*/

#include "server.h"

/**
 * @brief Add sibur to map's cell.
 *
 * @param map Map's cell.
 */
void add_sibur(map_t *map, int *rock)
{
    if (map->ressources.sibur >= 3)
        return;
    if (*rock == 3) {
        map->ressources.sibur += 1;
    }
}

/**
 * @brief Add sibur to map's cell.
 *
 * @param map Map's cell.
 */
void add_sibur_simple(map_t *map)
{
    if (map->ressources.sibur < 3)
        map->ressources.sibur += 1;
}