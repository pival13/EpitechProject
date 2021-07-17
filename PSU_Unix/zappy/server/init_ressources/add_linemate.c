/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** add_linemate
*/

#include "server.h"

/**
 * @brief Add linemate to map's cell.
 *
 * @param map Map's cell.
 */
void add_linemate(map_t *map, int *rock)
{
    if (map->ressources.linemate >= 3)
        return;
    if (*rock == 1) {
        *rock = 0;
        map->ressources.linemate += 1;
    }
}

/**
 * @brief Add linemate to map's cell.
 *
 * @param map Map's cell.
 */
void add_linemate_simple(map_t *map)
{
    if (map->ressources.linemate < 3)
        map->ressources.linemate += 1;
}