/*
** EPITECH PROJECT, 2019
** imperfect
** File description:
** map
*/

#include "dante.h"

void not_perf(char **map)
{
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\0'; j++)
            if (map[i][j] == 'X' && rand() % 5 == 0)
                map[i][j] = '*';
}