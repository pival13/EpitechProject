/*
** EPITECH PROJECT, 2019
** destroy_map
** File description:
** destroy the map
*/

#include <stdlib.h>

void destroy_map(char **map)
{
    for (int i = 0; map[i] != NULL; i++)
        free(map[i]);
    free(map);
}
