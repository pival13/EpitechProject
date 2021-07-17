/*
** EPITECH PROJECT, 2019
** hunt_kill
** File description:
** hunt and kill algo
*/

#include "dante.h"

int is_completed(char **map)
{
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\0'; j++)
            if (map[i][j] != '*' && map[i][j] != 'X')
                return (0);
    return (1);
}

int is_block(char **map, int x, int y)
{
    if (map[y][x+1] != '\0' && map[y][x+2] == '.')
        return (0);
    if (x > 1 && map[y][x-2] == '.')
        return (0);
    if (y > 1 && map[y-2][x] == '.')
        return (0);
    if (map[y+1] != NULL && map[y+2] != NULL && map[y+2][x] == '.')
        return (0);
    return (1);
}

int is_good_cell(char **map, int x, int y)
{
    if (x < 0 || y < 0)
        return (-1);
    if ((y > 0 && map[y-1] == NULL) || map[y] == NULL)
        return (-1);
    if ((x > 0 && map[y][x-1] == '\0') || map[y][x] == '\0')
        return (-1);
    if (map[y][x] != '.')
        return (0);
    return (1);
}