/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** add_deraumere
*/

#include "server.h"

/**
 * @brief Add deraumere to map's cell
 *
 * @param map Map's cell
 */
void add_deraumere(map_t *map, int *rock)
{
    if (map->ressources.deraumere >= 3)
        return;
    if (*rock == 4) {
        map->ressources.deraumere += 1;
        *rock = 0;
    }
}

/**
 * @brief Add deraumere to map's cell
 *
 * @param map Map's cell
 */
void add_deraumere_simple(map_t *map)
{
    if (map->ressources.deraumere < 3)
        map->ressources.deraumere += 1;
}